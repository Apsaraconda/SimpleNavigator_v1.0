#ifndef A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_CLI_S21_CLI
#define A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_CLI_S21_CLI

#include <ncurses.h>
#include <unistd.h>

#include <atomic>
#include <thread>

#include "../s21_graph_algorithms/s21_graph_algorithms.h"

namespace s21 {

class CLI {
 public:
  CLI() { stop_spinner_ = false; }
  int Exec();

 private:
  void ErrorHandle(int error);
  void EscapeCheck();
  void RedefineChForApple();
  int ValidateSym();
  void PathSymHandle(int &error);
  void RedrawWindow();
  void Menu();
  void MenuSymHandle(int &error);
  int ValidateMenuSym();
  void LoadPath();
  void ShowMenu();
  void PrintResultVector(std::vector<int> result);
  void SwitchAlgo();
  void PrintResultMatrix(std::vector<std::vector<int>> result);
  int SelectNumber(const char *description, int max_vertex);
  void ShortestPath();
  int ValidateVertexSym();
  void VertexSymHandle(int &vertex, int max_vertex, int &success, int start_x);
  void TraverseAlgos();
  void TSMAlgo();
  void TSMCompare();
  void RollingCursor();
  Graph graph_;
  GraphAlgorithms algo_;
  std::string path_;
  int ch_;
  std::atomic<bool> stop_spinner_;
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V_1_0_CPP_1_SRC_CLI_S21_CLI