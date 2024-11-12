#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>

#include "../../brick_game/tetris/s21_tetris.h"
#define ROWS 20
#define COLS 10
// #define COLOR_PAIR(F, B) ((chtype)(((F) << 8) | (B)))
#define GREEN 1
#define WHITE 2
#define BLUE 3

// Field
void PrintColor(char Table[ROWS][COLS], char Buffer[ROWS][COLS]);
void AdditionalInformation(int score, int maxScore);
void Pause_not();
void color_start();
void color_over();
// Figure
void color_figure();

#endif