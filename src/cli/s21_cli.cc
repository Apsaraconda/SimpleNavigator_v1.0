#include "s21_cli.h"

namespace s21 {

int CLI::Exec() {
  int error = 0;
  initscr();  //  Включение ncurses-режима
  cbreak();  //  Включение режима построчного ввода (без Enter)
  noecho();  //  Отключение отображения нажатых символов
  keypad(stdscr, TRUE);  //  Включение поддержки функциональных клавиш (ESC)
  scrollok(stdscr, TRUE);  //  Включение режима скроллинга экрана
  mvprintw(0, 0,
           "Hello! First I need to load an original graph from a file.\n");
  RedrawWindow();
  LoadPath();
  Menu();
  endwin();  //  Отключение ncurses-режима
  return error;
};

void CLI::ErrorHandle(int error) {
  switch (error) {
    case 1:
      printw("Error: Can't open file or file does not exists!\n");
      RedrawWindow();
      break;
    case 2:
      printw(
          "Error: Incorrect format, one or more vertices is not connected"
          "\n       in the loaded graph, or you try to load directed graph.\n");
      RedrawWindow();
      break;
    case 3:
      printw("Error: Loaded graph is not weighted!\n");
      RedrawWindow();
      break;
  }
}

void CLI::EscapeCheck() {
  if (ch_ == 27) {
    printw("<ESC> was pressed. The program is terminating...\n");
    RedrawWindow();
    sleep(1);
    endwin();
    exit(0);
  }
  RedefineChForApple();
}

void CLI::RedefineChForApple() {
#ifdef __APPLE__
  switch (ch_) {
    case 127:
      ch_ = KEY_BACKSPACE;
      break;
    case 330:
      ch_ = KEY_DC;
      break;
    case 260:
      ch_ = KEY_LEFT;
      break;
    case 261:
      ch_ = KEY_RIGHT;
      break;
    case 259:
      ch_ = KEY_UP;
      break;
    case 258:
      ch_ = KEY_DOWN;
      break;
    case 262:
      ch_ = KEY_HOME;
      break;
    case 360:
      ch_ = KEY_END;
      break;
    case 339:
      ch_ = KEY_PPAGE;
      break;
    case 338:
      ch_ = KEY_NPAGE;
      break;
    case -1:
      ch_ = KEY_RESIZE;
      break;
    default:
      break;
  }
#endif
}

int CLI::ValidateSym() {
  int success = 1;
  switch (ch_) {
    case KEY_F(1):
    case KEY_F(2):
    case KEY_F(3):
    case KEY_F(4):
    case KEY_F(5):
    case KEY_F(6):
    case KEY_F(7):
    case KEY_F(8):
    case KEY_F(9):
    case KEY_F(10):
    case KEY_F(11):
    case KEY_F(12):
    case KEY_DOWN:
    case KEY_UP:
    case KEY_RIGHT:
    case KEY_LEFT:
    case KEY_BACKSPACE:
    case KEY_DC:
    case KEY_HOME:
    case KEY_END:
    case KEY_IC:
    case KEY_NPAGE:
    case KEY_PPAGE:
      success = 0;
      break;
    case KEY_RESIZE:
      RedrawWindow();
      break;
    default:
      break;
  }
  return success;
}

// Функция для перерисовки содержимого окна
void CLI::RedrawWindow() {
  int height, width;
  getmaxyx(stdscr, height, width);  // Получаем новые размеры окна
  setscrreg(0, height - 2);  //  Установка области печати
  int y, x;
  getyx(stdscr, y, x);  //  Текущее положение курсора
  if (y == (height - 1)) y = height - 2;
  clrtobot();  //  Очистка экрана ниже положения курсора
  mvprintw(height - 1, 0, "Press <ESC> for exit.");
  move(y, x);  //  Возвращаем курсор на прежнюю позицию
  refresh();  // Обновляем экран для отображения изменений
}

}  // namespace s21
