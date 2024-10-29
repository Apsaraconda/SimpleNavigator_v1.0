#include "s21_graph_algorithms.h"

#include <cmath>
#include <limits>

#include "../s21_containers/s21_queue.h"
#include "../s21_containers/s21_stack.h"

namespace s21 {

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph& graph,
                                                   int start_vertex) {
  std::vector<int> result;
  int vertices_count = graph.GetVerticesCount();
  if (start_vertex > vertices_count || start_vertex < 1) {
    return result;
  }
  std::vector<bool> visited(vertices_count, false);
  s21::stack<int> stack;
  visited[start_vertex] = true;
  stack.push(start_vertex);
  while (!stack.empty()) {
    int vertex = stack.top();
    stack.pop();
    result.push_back(vertex);
    std::vector<int> adjacents = graph.GetAdjacentVertices(vertex);
    for (int v : adjacents) {
      if (!visited[v]) {
        visited[v] = true;
        stack.push(v);
      }
    }
  }
  return result;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph& graph,
                                                     int start_vertex) {
  std::vector<int> result;
  int vertices_count = graph.GetVerticesCount();
  if (start_vertex > vertices_count || start_vertex < 1) {
    return result;
  }
  std::vector<bool> visited(vertices_count, false);
  s21::queue<int> queue;
  visited[start_vertex] = true;
  queue.push(start_vertex);
  while (!queue.empty()) {
    int vertex = queue.front();
    queue.pop();
    result.push_back(vertex);
    std::vector<int> adjacents = graph.GetAdjacentVertices(vertex);
    for (int v : adjacents) {
      if (!visited[v]) {
        visited[v] = true;
        queue.push(v);
      }
    }
  }
  return result;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph& graph, int vertex1,
                                                    int vertex2) {
  int result = 0;
  if (vertex1 == vertex2) {
    result = graph.GetVergeWeight(vertex1, vertex2);
  } else {
    int verticesCount = graph.GetVerticesCount();
    std::vector<int> distances(verticesCount + 1,
                               std::numeric_limits<int>::max());
    distances[vertex1] = 0;
    s21::queue<int> queue;
    queue.push(vertex1);
    std::set<int> visited;
    while (!queue.empty()) {
      int currentVertex = queue.front();
      queue.pop();
      if (visited.find(currentVertex) != visited.end()) {
        continue;  // Пропускаем уже посещенные вершины
      }
      visited.insert(currentVertex);
      for (int neighbor : graph.GetAdjacentVertices(currentVertex)) {
        int weight = graph.GetVergeWeight(currentVertex, neighbor);
        int newDistance = distances[currentVertex] + weight;
        if (newDistance < distances[neighbor]) {
          distances[neighbor] = newDistance;
          queue.push(neighbor);  // Добавляем соседа в очередь
        }
      }
    }
    result = distances[vertex2];
  }
  return result;
}

std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph& graph) {
  int verticesCount = graph.GetVerticesCount();
  std::vector<std::vector<int>> distance(
      verticesCount,
      std::vector<int>(verticesCount, std::numeric_limits<int>::max()));

  // Инициализация матрицы расстояний
  for (int i = 0; i < verticesCount; ++i) {
    distance[i][i] = 0;  // Расстояние до самого себя равно 0
    for (int j = 0; j < verticesCount; ++j) {
      if (i != j) {
        int weight =
            graph.GetVergeWeight(i + 1, j + 1);  // Индексация вершин с 1
        if (weight > 0) {  // Проверка существования ребра
          distance[i][j] = weight;
        }
      }
    }
  }

  // Алгоритм Флойда-Уоршелла
  for (int k = 0; k < verticesCount; ++k) {
    for (int i = 0; i < verticesCount; ++i) {
      for (int j = 0; j < verticesCount; ++j) {
        if (distance[i][k] != std::numeric_limits<int>::max() &&
            distance[k][j] != std::numeric_limits<int>::max()) {
          distance[i][j] =
              std::min(distance[i][j], distance[i][k] + distance[k][j]);
        }
      }
    }
  }

  return distance;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph& graph) {
  return SolveTravelingSalesmanProblemAnt(graph);
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblemAnt(Graph& graph) {
  AntColony antColony(graph);
  return antColony.Solve(1);
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblemGreedy(Graph& graph) {
  GreedyTSP greedyTsp(graph);
  return greedyTsp.Solve(1);
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblemBrute(Graph& graph) {
  BruteForceTSP bruteTsp(graph);
  return bruteTsp.Solve(1);
}

TsmCompare GraphAlgorithms::SolveTravelingSalesmanProblemCompare(
    Graph& graph, int iterationLimit) {
  TsmCompare tsmCompare;
  tsmCompare.overflow_error = false;
  AntColony antColony(graph);
  GreedyTSP greedyTsp(graph);
  BruteForceTSP bruteTsp(graph);
  auto startTime = std::chrono::steady_clock::now();
  auto endTime = std::chrono::steady_clock::now();

  startTime = std::chrono::steady_clock::now();
  for (int i = 0; i < iterationLimit; ++i) {
    antColony.Solve(1);
  }
  endTime = std::chrono::steady_clock::now();
  tsmCompare.overflow_error =
      CheckDuration(endTime, startTime, tsmCompare.antColonyTime);

  if (!tsmCompare.overflow_error) {
    startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < iterationLimit; ++i) {
      greedyTsp.Solve(1);
    }
    endTime = std::chrono::steady_clock::now();
    tsmCompare.overflow_error =
        CheckDuration(endTime, startTime, tsmCompare.greedyTime);
  }
  if (!tsmCompare.overflow_error) {
    startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < iterationLimit; ++i) {
      bruteTsp.Solve(1);
    }
    endTime = std::chrono::steady_clock::now();
    tsmCompare.overflow_error =
        CheckDuration(endTime, startTime, tsmCompare.bruteForceTime);
  }
  return tsmCompare;
}

bool GraphAlgorithms::CheckDuration(
    std::chrono::_V2::steady_clock::time_point end_time,
    std::chrono::_V2::steady_clock::time_point start_time, int64_t& result) {
  bool error = false;
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                      end_time - start_time)
                      .count();
  if (duration > std::numeric_limits<int64_t>::max() ||
      duration < std::numeric_limits<int64_t>::min()) {
    error = true;
  } else {
    result = duration;
  }
  return error;
}

}  // namespace s21