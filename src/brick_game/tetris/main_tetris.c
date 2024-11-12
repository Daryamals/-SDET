#include "s21_tetris.h"

extern const Figure SamplesFigure[];

int main() {
  srand(time(0));
  char Table[ROWS][COLS] = {0};
  for (int i = 0; i <= ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (i == 19 || i == 0 || j == 0 || j == 9) Table[i][j] = 3;
      // if (i == -1) Table[i][j] = 3;
    }
  }

  int score = 0;
  int maxScore = 0;
  LoadGame(&maxScore);
  int Stop = 1;
  bool GameOn = TRUE;
  int action;
  struct timeval before, after;
  memset(&before, 0, sizeof(before));
  Figure CurrentFigure;
  initscr();              // для инициализации ncurses.
  nodelay(stdscr, TRUE);  // функция getch() не будет блокировать выполнение
  // программы, если нет ввода от пользователя. т.е. это установка режима
  // неожидания для окна stdscr
  start_color();
  CreateFigure(&CurrentFigure, Table, &GameOn);
  color_start();
  while (GameOn) {
    if ((action = getch()) != ERR) {
      InputUser(action, &GameOn, &CurrentFigure, Table, &score, &Stop,
                maxScore);
    } else {
      if (!Stop) {
        gettimeofday(&after, NULL);
        if (((double)after.tv_sec * 1000000 + (double)after.tv_usec) -
                ((double)before.tv_sec * 1000000 + (double)before.tv_usec) >
            1000000 - level(score)) {
          action = 's';
          InputUser(action, &GameOn, &CurrentFigure, Table, &score, &Stop,
                    maxScore);
          before = after;
        }
        if (action != ' ') {
          Pause_not();
        }
      }
    }
  }
  // clear();
  // color_over();
  SaveGame(score, maxScore);
  // refresh();
  endwin();
  printf("\nGame over\n");
  return 0;
}