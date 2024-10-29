#include "s21_cli.h"

namespace s21 {

void CLI::SwitchAlgo() {
  std::vector<std::vector<int>> result_matrix;
  printw("You've chosen:\n");
  switch (ch_) {
    case 50:
      printw("2: Traverse the graph in breadth.\n");
      TraverseAlgos();
      break;
    case 51:
      printw("3: Traverse the graph in depth.\n");
      TraverseAlgos();
      break;
    case 52:
      printw("4: Search for the shortest path between any two vertices.\n");
      ShortestPath();
      break;
    case 53:
      printw(
          "5: Search for the shortest paths between all pairs of vertices in "
          "the graph.\n");
      result_matrix = algo_.GetShortestPathsBetweenAllVertices(graph_);
      PrintResultMatrix(result_matrix);
      break;
    case 54:
      printw("6: Search for the minimum spanning tree in the graph.\n");
      result_matrix = algo_.GetLeastSpanningTree(graph_);
      PrintResultMatrix(result_matrix);
      break;
    case 55:
      printw("7: Solve the Traveling Salesman problem.\n");
      TSMAlgo();
      break;
    case 56:
      printw(
          "8: Compare the speed of solving the Salesman problem\n"
          "   using ant colony, greedy algorithm and brute force.\n");
      TSMCompare();
      break;
    default:
      break;
  }
}

void CLI::TSMCompare() {
  TsmResult tsm_result = algo_.SolveTravelingSalesmanProblem(graph_);
  if (tsm_result.distance && tsm_result.vertices.size()) {
    int iteration_limit = SelectNumber("iteration limit", 1000);
    if (iteration_limit) {
      stop_spinner_ = false;
      std::thread spinner_thread(&CLI::RollingCursor, this);
      TsmCompare result =
          algo_.SolveTravelingSalesmanProblemCompare(graph_, iteration_limit);
      stop_spinner_ = true;
      spinner_thread.join();
      printw("\tResult:\n");
      if (!result.overflow_error) {
        printw("\tAnt colony algorithm time: %ld microsec.\n",
               result.antColonyTime);
        printw("\tGreedy algorithm time: %ld microsec.\n", result.greedyTime);
        printw("\tBrute force algorithm time: %ld microsec.\n",
               result.bruteForceTime);
      } else {
        printw("Error: The calculation is taking longer than expected. \n");
      }
    } else {
      printw("Error: Iteration limit must be not zero!\n");
    }
  } else {
    printw("\tResult:\n");
    printw("\tThe graph has no solution to the Traveling Salesman problem.\n");
  }
  printw("Enter next function number or press <Enter> to show main menu.\n");
  RedrawWindow();
}

void CLI::RollingCursor() {
  const char cursor[] = {'|', '/', '-', '\\'};
  int i = 0;
  int y, x;
  getyx(stdscr, y, x);
  while (!stop_spinner_) {
    mvprintw(y, x, "%c", cursor[i % 4]);
    RedrawWindow();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    i++;
  }
  getyx(stdscr, y, x);
  move(y, x - 1);
  delch();
  RedrawWindow();
}

void CLI::TSMAlgo() {
  stop_spinner_ = false;
  std::thread spinner_thread(&CLI::RollingCursor, this);
  TsmResult tsm_result = algo_.SolveTravelingSalesmanProblem(graph_);
  stop_spinner_ = true;
  spinner_thread.join();
  if (tsm_result.distance && tsm_result.vertices.size()) {
    printw("\tRoute length = ");
    std::string distance =
        std::to_string((long unsigned int)tsm_result.distance);
    const char *c = distance.c_str();
    printw("%s\n", c);
    PrintResultVector(tsm_result.vertices);
  } else {
    printw("\tResult:\n");
    printw("\tThe graph has no solution to the Traveling Salesman problem.\n");
    printw("Enter next function number or press <Enter> to show main menu.\n");
    RedrawWindow();
  }
}

void CLI::TraverseAlgos() {
  std::vector<int> result;
  int vertex = 0;
  vertex = SelectNumber("starting vertex", graph_.GetVerticesCount());
  if (vertex) {
    if (ch_ == 50) {
      result = algo_.BreadthFirstSearch(graph_, vertex);
    } else {
      result = algo_.DepthFirstSearch(graph_, vertex);
    }
    PrintResultVector(result);
  } else {
    printw("Error: Vertex must be not zero!\n");
    printw("Enter next function number or press <Enter> to show main menu.\n");
    RedrawWindow();
  }
}

void CLI::ShortestPath() {
  int first_vertex = SelectNumber("first vertex", graph_.GetVerticesCount());
  if (first_vertex) {
    int second_vertex =
        SelectNumber("second vertex", graph_.GetVerticesCount());
    if (second_vertex) {
      int result = algo_.GetShortestPathBetweenVertices(graph_, first_vertex,
                                                        second_vertex);
      printw("\tRoute length = ");
      printw("%d\n", result);
    } else {
      printw("Error: Vertex must be not zero!\n");
    }
  } else {
    printw("Error: Vertex must be not zero!\n");
  }
  printw("Enter next function number or press <Enter> to show main menu.\n");
  RedrawWindow();
}

}  // namespace s21