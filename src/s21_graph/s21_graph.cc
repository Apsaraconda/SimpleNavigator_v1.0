#include "s21_graph.h"

namespace s21 {

int Graph::GetVal(int x, int y, int *value) {
  int error = 0;
  if (x < n_ && y < n_) {
    *value = matrix_[x][y];
  } else {
    error = 1;
  }
  return error;
}

void Graph::ClearData() {
  n_ = 0;
  matrix_.clear();
  matrix_.resize(0, std::vector<int>(0, 0));
}

int Graph::CheckDirWeight() {
  int error = 0;
  int weights = 0;
  int count = GetVerticesCount();
  for (int i = 0; i < count; i++) {
    int bounds = 0;
    for (int j = 0; j < count; j++) {
      if (matrix_[i][j] != matrix_[j][i]) error = 2;
      if (matrix_[i][j] != 0 && matrix_[i][j] != 1) weights = 1;
      bounds = bounds + matrix_[i][j];
    }
    if (!bounds) error = 2;
  }
  if (!weights) error = 3;
  return error;
}

std::vector<int> Graph::GetAdjacentVertices(int vertex) {
  std::vector<int> result;
  int count = GetVerticesCount();
  if (vertex <= count && vertex > 0) {
    for (int i = count - 1; i >= 0; i--) {
      if (matrix_[i][vertex - 1] != 0 && i != (vertex - 1))
        result.push_back(i + 1);
    }
  }
  return result;
}

}  // namespace s21