#include "s21_graph_algorithms.h"

namespace s21 {

std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  std::vector<std::vector<int>> result(
      graph.GetVerticesCount(), std::vector<int>(graph.GetVerticesCount(), 0));
  int count = graph.GetVerticesCount();
  std::vector<bool> selected(count, false);
  int unselected = graph.GetVerticesCount();
  selected[0] = true;
  while (unselected > 0) {
    int min = MAX_GRAPH_SIZE;
    int x = 0;
    int y = 0;
    for (int i = 0; i < count; i++) {
      if (selected[i] == true) {  //  проходим по всем выбранным ранее вершинам
        for (int j = 0; j < count; j++) {
          if (!selected[j] && graph.GetVergeWeight(i + 1, j + 1)) {
            if (min > graph.GetVergeWeight(i + 1, j + 1)) {
              min = graph.GetVergeWeight(i + 1, j + 1);
              x = i;
              y = j;
            }
          }
        }
      }
    }
    selected[y] = true;
    unselected--;
    if (x == 0 && y == 0) {
      result[x][y] = 0;
    } else {
      result[y][x] = min;
      result[x][y] = min;
    }
  }
  return result;
}

}  // namespace s21