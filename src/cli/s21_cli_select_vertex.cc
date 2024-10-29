#include "s21_cli.h"

namespace s21 {

int CLI::SelectNumber(const char *description, int max_number) {
  printw("Select %s between 1 and %d inclusive and press <Enter>: ",
         description, max_number);
  RedrawWindow();
  int vertex = 0;
  int success = 0;
  int start_y, start_x;
  getyx(stdscr, start_y, start_x);
  ch_ = start_y;
  while (!success) {
    ch_ = getch();
    EscapeCheck();
    VertexSymHandle(vertex, max_number, success, start_x);
  }
  printw("\n");
  RedrawWindow();
  return vertex;
}

void CLI::VertexSymHandle(int &vertex, int max_vertex, int &success,
                          int start_x) {
  if (ValidateVertexSym()) {
    if (ch_ != '\n' && ch_ != KEY_BACKSPACE &&
        (vertex <= MAX_GRAPH_SIZE / 10)) {
      int result;
      if (!__builtin_add_overflow(vertex * 10, (ch_ - 48), &result) &&
          result <= max_vertex) {
        vertex = vertex * 10 + ch_ - 48;
        printw("%d", (ch_ - 48));
        RedrawWindow();
      }
    } else if (ch_ == '\n') {
      success = 1;
    } else if (ch_ == KEY_BACKSPACE) {
      if (vertex) vertex = vertex / 10;
      int y, x;
      getyx(stdscr, y, x);
      if (x > start_x) {
        move(y, x - 1);
        delch();
        RedrawWindow();
      }
    }
  }
}

int CLI::ValidateVertexSym() {
  int success = 1;
  if ((ch_ < 48 || ch_ > 57) && (ch_ != '\n') && (ch_ != KEY_BACKSPACE)) {
    success = 0;
  }
  return success;
}

}  // namespace s21