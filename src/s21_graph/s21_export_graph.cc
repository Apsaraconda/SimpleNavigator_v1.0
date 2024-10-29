#include "s21_graph.h"

namespace s21 {

int Graph::ExportGraphToDot(std::string filename) {
  int error = 0;
  if (!std::filesystem::exists(filename)) {
    std::ofstream out;  // поток для записи
    out.open(filename, std::ios::app);  // открываем файл для добавления
    if (!out.is_open()) {
      error = 1;
    } else {
      ExportToStream(&out);
      out.close();
    }
  } else {
    error = 4;
  }
  return error;
}

void Graph::ExportToStream(std::ofstream *out) {
  *out << "graph {\n";
  int count = GetVerticesCount();
  for (int i = 1; i <= count; i++) *out << "    " << i << ";\n";
  for (int row = 0; row < count; row++) {
    for (int col = 0; col < count; col++) {
      if (matrix_[row][col] != 0 && row <= col) {
        *out << "    " << row + 1 << " -";
        *out << "- ";
        *out << col + 1;
        *out << " [ label = \"" << matrix_[row][col] << "\"]";
        *out << ";\n";
      }
    }
  }
  *out << "}";
}

}  // namespace s21