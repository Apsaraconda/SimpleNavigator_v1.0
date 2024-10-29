#include "s21_graph.h"

namespace s21 {

int Graph::LoadGraphFromFile(std::string filename) {
  int error = 0;
  std::filesystem::path path_to_file = filename;
  std::ifstream file(filename);
  if (!file.is_open() || !std::filesystem::is_regular_file(path_to_file)) {
    error = 1;
  } else {
    ClearData();
    int current_line = 0;
    std::string line;
    while (std::getline(file, line)) {
      std::stringstream ss(line);
      std::string word;
      std::vector<std::string> line_data;
      while (ss >> word) {
        line_data.push_back(word);
      }
      LineHandle(line_data, &current_line, &error);
      if (error) break;
    }
    if (!error) error = CheckDirWeight();
    file.close();
  }
  return error;
}

void Graph::LineHandle(std::vector<std::string> line_data, int *current_line,
                       int *error) {
  if (*current_line == 0) {
    if (line_data.size() == 1) {
      try {
        long unsigned int value = std::stoul(line_data[0]);
        n_ = value;
      } catch (...) {
        *error = 2;
      }
    } else if (line_data.size() != 0 && line_data.size() <= MAX_GRAPH_SIZE) {
      n_ = line_data.size();
      matrix_.resize(line_data.size(), std::vector<int>(0, 0));
      *error = PushVal(line_data, *current_line);
      *current_line = *current_line + 1;
    } else if (line_data.size() != 0) {
      *error = 2;
    }
  } else {
    if (line_data.size() <= MAX_GRAPH_SIZE) {
      int size = line_data.size();
      if (size == GetVerticesCount() && *current_line < GetVerticesCount()) {
        *error = PushVal(line_data, *current_line);
        *current_line = *current_line + 1;
      } else if (size != GetVerticesCount() &&
                 *current_line < GetVerticesCount()) {
        *error = 2;
      }
    } else {
      *error = 2;
    }
  }
}

int Graph::PushVal(std::vector<std::string> line_data, int row) {
  int error = 0;
  int size = line_data.size();
  for (int i = 0; i < size; ++i) {
    try {
      long unsigned int value = std::stoul(line_data[i]);
      matrix_[row].push_back(value);
    } catch (...) {
      error = 2;
      break;
    }
  }
  return error;
}

}  // namespace s21