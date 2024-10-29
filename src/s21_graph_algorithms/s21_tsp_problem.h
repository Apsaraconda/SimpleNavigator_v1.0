#ifndef A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_S21_GRAPH_ALGORITHMS_S21_TSP_PROBLEM_H
#define A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_S21_GRAPH_ALGORITHMS_S21_TSP_PROBLEM_H

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <vector>

#include "../s21_graph/s21_graph.h"

namespace s21 {

struct TsmResult {
  std::vector<int>
      vertices;  // массив с искомым маршрутом (с порядком обхода вершин).
  double distance;  // длина этого маршрута
};

class AntColony {
 public:
  AntColony(Graph& graph) : graph_(graph) {
    verticesCount_ = graph.GetVerticesCount();
    pheromones_.resize(verticesCount_,
                       std::vector<double>(verticesCount_, 1.0));
  }

  TsmResult Solve(int startVertex) {
    std::vector<int> bestPath;
    double bestCost = std::numeric_limits<double>::max();

    // Выполняем несколько итераций
    for (int i = 0; i < iterations_; ++i) {
      auto path = ConstructPath(startVertex - 1);
      if (path.size() == verticesCount_) {
        if (graph_.GetVergeWeight(startVertex, path.back()) > 0) {
          double cost = CalculatePathCost(path);
          cost += graph_.GetVergeWeight(startVertex, path.back());
          if (cost < bestCost) {
            bestCost = cost;
            bestPath = path;
          }
        }
        UpdatePheromones(path, bestCost);
      }
    }

    TsmResult result = {};
    if (bestPath.size() != verticesCount_) {
      return result;
    }
    bestPath.push_back(startVertex);
    result.vertices = std::move(bestPath);
    for (size_t i = 0; i < result.vertices.size() - 1; ++i) {
      result.distance +=
          graph_.GetVergeWeight(result.vertices[i], result.vertices[i + 1]);
    }

    return result;
  }

 private:
  size_t verticesCount_;
  Graph& graph_;
  std::vector<std::vector<double>> pheromones_;
  int iterations_ = 100;
  double decayFactor_ = 0.95;

  std::vector<int> ConstructPath(int startVertex) {
    std::vector<bool> visited(verticesCount_, false);
    std::vector<int> path;
    visited[startVertex] = true;
    path.push_back(startVertex + 1);  // Сохраняем 1-индексированный

    for (size_t step = 1; step < verticesCount_; ++step) {
      int currentVertex = path.back() - 1;
      int nextVertex = SelectNextVertex(currentVertex, visited);
      if (nextVertex == -1) break;  // Нет доступных соседей
      visited[nextVertex] = true;
      path.push_back(nextVertex + 1);  // Сохраняем 1-индексированный
    }

    return path;
  }

  int SelectNextVertex(int currentVertex, const std::vector<bool>& visited) {
    double total = 0;
    std::vector<double> probabilities(verticesCount_, 0.0);

    auto adjacentVertices = graph_.GetAdjacentVertices(currentVertex + 1);
    for (int neighbor : adjacentVertices) {
      int neighborIndex = neighbor - 1;
      if (!visited[neighborIndex]) {
        double edgeWeight = graph_.GetVergeWeight(currentVertex + 1, neighbor);
        probabilities[neighborIndex] =
            pheromones_[currentVertex][neighborIndex] / edgeWeight;
        total += probabilities[neighborIndex];
      }
    }

    if (total == 0) return -1;  // Если нет доступных соседей

    double random = static_cast<double>(rand()) / RAND_MAX;
    double cumulative = 0.0;

    for (size_t i = 0; i < verticesCount_; ++i) {
      if (probabilities[i] > 0) {
        cumulative += probabilities[i] / total;
        if (cumulative >= random) {
          return i;
        }
      }
    }

    return -1;  // Нет доступного соседа
  }

  double CalculatePathCost(const std::vector<int>& path) {
    double cost = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
      cost += graph_.GetVergeWeight(path[i], path[i + 1]);
    }
    return cost;
  }

  void UpdatePheromones(const std::vector<int>& path, double cost) {
    double pheromoneIncrease = 1.0 / cost;

    for (size_t i = 0; i < path.size() - 1; ++i) {
      int current = path[i] - 1;
      int next = path[i + 1] - 1;  // Следующий
      pheromones_[current][next] += pheromoneIncrease;
      pheromones_[next][current] += pheromoneIncrease;  // Обратный путь
    }

    for (auto& row : pheromones_) {
      for (auto& value : row) {
        value *= decayFactor_;  // Уменьшение феромонов
      }
    }
  }
};

class GreedyTSP {
 public:
  GreedyTSP(Graph& graph) : graph_(graph) {
    verticesCount_ = graph.GetVerticesCount();
  }

  TsmResult Solve(int startVertex) {
    std::vector<bool> visited(verticesCount_, false);
    std::vector<int> path;
    double totalDistance = 0.0;

    int currentVertex = startVertex - 1;
    path.push_back(currentVertex + 1);
    visited[currentVertex] = true;

    for (size_t step = 1; step < verticesCount_; ++step) {
      int nextVertex = -1;
      double minWeight = std::numeric_limits<double>::max();

      auto adjacentVertices = graph_.GetAdjacentVertices(currentVertex + 1);
      for (int neighbor : adjacentVertices) {
        int neighborIndex = neighbor - 1;
        if (!visited[neighborIndex]) {
          double weight = graph_.GetVergeWeight(currentVertex + 1, neighbor);
          if (weight < minWeight) {
            minWeight = weight;
            nextVertex = neighborIndex;
          }
        }
      }

      if (nextVertex == -1) {
        return {};  // Нет доступного соседа, возвращаем пустую структуру
      }

      visited[nextVertex] = true;
      path.push_back(nextVertex + 1);
      totalDistance += minWeight;
      currentVertex = nextVertex;
    }

    TsmResult result = {};
    if (graph_.GetVergeWeight(startVertex, path.back()) <= 0) {
      return result;
    }

    // Замыкаем цикл, добавляя путь к начальной вершине
    totalDistance += graph_.GetVergeWeight(startVertex, path.back());
    path.push_back(startVertex);  // Возвращаемся в начальную вершину

    result.vertices = std::move(path);
    result.distance = totalDistance;

    return result;
  }

 private:
  size_t verticesCount_;
  Graph& graph_;
};

class BruteForceTSP {
 public:
  BruteForceTSP(Graph& graph) : graph_(graph) {
    verticesCount_ = graph.GetVerticesCount();
  }

  TsmResult Solve(int startVertex, int64_t timeLimitMilliseconds = 5000) {
    std::vector<int> vertices(verticesCount_);
    for (size_t i = 0; i < verticesCount_; ++i) {
      vertices[i] = i + 1;  // Сохраняем 1-индексированный
    }

    TsmResult bestResult = {};
    bestResult.distance = std::numeric_limits<double>::max();

    auto startTime = std::chrono::steady_clock::now();

    do {
      bool validPermutation = true;  // Флаг для проверки корректности маршрута
      if (graph_.GetVergeWeight(startVertex, vertices.back()) <= 0) {
        validPermutation = false;  // Рассматриваем только положительные веса
      }
      if (validPermutation) {
        double totalDistance = 0.0;

        for (size_t i = 0; i < verticesCount_ - 1; ++i) {
          double distance = graph_.GetVergeWeight(vertices[i], vertices[i + 1]);
          if (distance <= 0) {  // Рассматриваем только положительные веса
            validPermutation = false;  // Найдено недопустимое ребро
            break;
          }
          totalDistance += distance;
        }

        // Если последняя проверка расстояния к начальной вершине
        totalDistance += graph_.GetVergeWeight(vertices.back(), startVertex);

        // Проверяем, валидна ли последовательность и обновляем лучшее значение
        if (validPermutation && totalDistance < bestResult.distance) {
          bestResult.vertices = vertices;
          bestResult.distance = totalDistance;
        }
      }

      // Проверка времени
      auto currentTime = std::chrono::steady_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                          currentTime - startTime)
                          .count();
      if (duration >= timeLimitMilliseconds) {
        break;  // Превышен лимит времени
      }

    } while (std::next_permutation(vertices.begin() + 1,
                                   vertices.end()));  // Для всех перестановок

    // Проверка на валидность возвращаемого результата
    if (bestResult.vertices.size() != verticesCount_ ||
        graph_.GetVergeWeight(startVertex, bestResult.vertices.back()) < 0) {
      return {};
    }

    bestResult.vertices.push_back(startVertex);  // Закрываем цикл

    return bestResult;
  }

 private:
  size_t verticesCount_;
  Graph& graph_;
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_S21_GRAPH_ALGORITHMS_S21_TSP_PROBLEM_H
