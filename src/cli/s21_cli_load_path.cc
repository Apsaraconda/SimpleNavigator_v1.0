#include "s21_cli.h"

namespace s21 {

void CLI::LoadPath() {
  printw("Please, enter a path to the file:\n");
  RedrawWindow();
  int error = 1;
  path_.clear();
  while (error) {
    ch_ = getch();
    EscapeCheck();
    PathSymHandle(error);
  }
}

void CLI::PathSymHandle(int &error) {
  if (ValidateSym()) {
    if (ch_ != KEY_RESIZE) printw("%c", (wchar_t)ch_);
    RedrawWindow();
    if (ch_ != (char)'\n' && ch_ != KEY_RESIZE) {
      path_.append(1, (wchar_t)ch_);
    } else if (ch_ == (char)'\n') {
      error = graph_.LoadGraphFromFile(path_);
      if (error) {
        ErrorHandle(error);
        printw("Please, enter a path to the file:\n");
        RedrawWindow();
        path_.clear();
      }
    }
  } else if (ch_ == KEY_BACKSPACE) {
    if (path_.size()) path_.erase(path_.end() - 1);
    int y, x;
    getyx(stdscr, y, x);
    if (x > 0) {
      move(y, x - 1);
      delch();
      RedrawWindow();
    }
  }
}

}  // namespace s21