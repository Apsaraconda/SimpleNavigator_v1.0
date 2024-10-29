#ifndef A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_S21_GRAPH_S21_GRAPH_H
#define A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_S21_GRAPH_S21_GRAPH_H
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define MAX_GRAPH_SIZE 2147483647

namespace s21 {

class Graph {
 public:
  Graph() : n_(0), matrix_(0, std::vector<int>(0, 0)) {}
  Graph(int n) : n_(n), matrix_(n, std::vector<int>(n, 0)) {}
  int LoadGraphFromFile(std::string filename);
  int ExportGraphToDot(std::string filename);
  void ClearData();
  int GetVerticesCount() { return n_; }
  int GetVal(int x, int y, int *value);
  int GetVergeWeight(int first, int second) {
    return matrix_[first - 1][second - 1];
  }
  std::vector<int> GetAdjacentVertices(int vertex);

 private:
  int PushVal(std::vector<std::string> line_data, int row);
  void LineHandle(std::vector<std::string> line_data, int *current_line,
                  int *error);
  int CheckSetRange(std::vector<std::string> line_data, int *form_success);
  void ExportToStream(std::ofstream *out);
  int CheckDirWeight();
  int n_;
  std::vector<std::vector<int>> matrix_;
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_S21_GRAPH_S21_GRAPH_H