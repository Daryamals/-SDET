
#include "s21_gui_tetris.h"

// В файле s21_gui_tetris.c
extern const Figure SamplesFigure[];

void AdditionalInformation(int score, int maxScore) {
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(GREEN));
  int scoreX = COLS + 20;
  int scoreY = ROWS / 2 - 4;
  mvwprintw(stdscr, scoreY, scoreX, "Score: %d", score);
  mvwprintw(stdscr, scoreY + 2, scoreX, "Max score: %d", maxScore);
  mvwprintw(stdscr, scoreY + 4, scoreX, "Speed: %d", level(score));

  attroff(COLOR_PAIR(GREEN));
}

void PrintColor(char Table[ROWS][COLS], char Buffer[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      (Table[i][j] + Buffer[i][j]) ? color_figure() : printw("%c ", '.');
    }
    printw("\n");
  }
}

void Pause_not() {
  init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
  attron(COLOR_PAIR(WHITE));
  int textX = COLS + 20;
  int textY = ROWS - ROWS + 1;
  mvwprintw(stdscr, textY, textX, "Push space for pause game");
  attroff(COLOR_PAIR(WHITE));
}

void color_start() {
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(GREEN));
  printw("game control:\n");
  printw("1. Space - start/pause game:\n");
  printw("2. O - finish game:\n");
  printw("3. w,s,a,d - movement fugure:\n");
  printw("\n\nPush space for start!");
  attroff(COLOR_PAIR(GREEN));
}

void color_over() {
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(GREEN));
  printw("\nGame over\n");
  attroff(COLOR_PAIR(GREEN));
}

void color_figure() {
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
  attron(COLOR_PAIR(BLUE));
  printw("%c ", 'O');
  attroff(COLOR_PAIR(BLUE));
}