#include "s21_cli.h"

namespace s21 {

void CLI::Menu() {
  ShowMenu();
  int error = 1;
  while (error) {
    ch_ = getch();
    EscapeCheck();
    MenuSymHandle(error);
  }
}

void CLI::MenuSymHandle(int &error) {
  if (ValidateSym()) {
    if (!ValidateMenuSym() && ch_ != 10) {
      if (ch_ != KEY_RESIZE) printw("Please, enter correct key.\n");
      RedrawWindow();
    } else {
      switch (ch_) {
        case 10:  //  '\n'
          ShowMenu();
          break;
        case 49:
          printw(
              "You've chosen:\n1: Load another original graph from a file.\n");
          RedrawWindow();
          LoadPath();
          ShowMenu();
          break;
        default:
          SwitchAlgo();
          break;
      }
    }
  }
  error = 1;
}

int CLI::ValidateMenuSym() {
  int success = 1;
  if (ch_ < 49 || ch_ > 56) {
    success = 0;
  }
  return success;
}

void CLI::ShowMenu() {
  for (int i = 0; i < 70; ++i) printw("*");
  printw("\nPlease, enter a function number code as described below:\n");
  printw("1: Load another original graph from a file.\n");
  printw(
      "2: Traverse the graph in breadth and print the result to the "
      "console.\n");
  printw(
      "3: Traverse the graph in depth and print the result to the console.\n");
  printw(
      "4: Find the shortest path between any two vertices\n   and print the "
      "result "
      "to the console.\n");
  printw(
      "5: Find the shortest paths between all pairs of vertices in the graph\n"
      "   and print the result matrix to the console.\n");
  printw(
      "6: Search for the minimum spanning tree in the graph\n   and print the "
      "resulting adjacency matrix to the console.\n");
  printw(
      "7: Solve the Salesman problem, with output of the resulting route\n   "
      "and print"
      "its length to the console.\n");
  printw(
      "8: Display a comparison of the speed of solving\n   the "
      "Salesman problem using three algorithms:\n"
      "   ant colony, greedy algorithm and brute force.\n");
  for (int i = 0; i < 70; ++i) printw("*");
  printw("\n");
  RedrawWindow();
}

void CLI::PrintResultVector(std::vector<int> result) {
  printw("\tResult:\n\t");
  for (unsigned long int i = 0; i < result.size(); ++i) {
    printw("%d ", result[i]);
  }
  printw("\nEnter next function number or press <Enter> to show main menu.\n");
  RedrawWindow();
}

void CLI::PrintResultMatrix(std::vector<std::vector<int>> result) {
  printw("\tResult:\n");
  for (unsigned long int i = 0; i < result.size(); ++i) {
    printw("\t");
    for (unsigned long int j = 0; j < result[i].size(); ++j) {
      printw("%d ", result[i][j]);
    }
    printw("\n");
  }
  printw("Enter next function number or press <Enter> to show main menu.\n");
  RedrawWindow();
}

}  // namespace s21
