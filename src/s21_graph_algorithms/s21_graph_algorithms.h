#ifndef A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_S21_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H
#define A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_S21_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H

#include <cstring>
#include <set>

#include "../s21_containers/s21_queue.h"
#include "../s21_graph/s21_graph.h"
#include "s21_tsp_problem.h"

namespace s21 {

struct TsmCompare {
  int64_t antColonyTime;
  int64_t greedyTime;
  int64_t bruteForceTime;
  bool overflow_error;
};

class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph &graph);
  std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);
  TsmResult SolveTravelingSalesmanProblemAnt(Graph &graph);
  TsmResult SolveTravelingSalesmanProblemGreedy(Graph &graph);
  TsmResult SolveTravelingSalesmanProblemBrute(Graph &graph);
  TsmCompare SolveTravelingSalesmanProblemCompare(Graph &graph,
                                                  int iterationLimit);

 private:
  bool CheckDuration(std::chrono::_V2::steady_clock::time_point end_time,
                     std::chrono::_V2::steady_clock::time_point start_time,
                     int64_t &result);
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_S21_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H