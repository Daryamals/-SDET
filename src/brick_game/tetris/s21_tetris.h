#ifndef TETRIS_H
#define TETRIS_H

#include <assert.h>
#include <check.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "../../gui/cli/s21_gui_tetris.h"

#define ROWS 20
#define COLS 10

typedef struct {  // структура для представления фигур в игры
  char samples[5][5];  // хранение массива, который представляет фигуру
  int width, row, col;  // ширина фигуры и текущия позиция
} Figure;

Figure CaptureFigure(Figure figure);
int level(int score);
void LoadGame(int *score);
void SaveGame(int score, int maxScore);
void UpdatePosition(char Buffer[ROWS][COLS], Figure CurrentFigure);

void PrintTable(char Table[ROWS][COLS], int *score, Figure CurrentFigure,
                int maxScore);
int CheckRuleS(Figure TempFigure, char Table[ROWS][COLS]);
int CheckRuleD(char Table[ROWS][COLS], Figure figure);
int CheckRuleA(char Table[ROWS][COLS], Figure figure);
int CheckRuleW(char Table[ROWS][COLS], Figure figure);
void WriteToTable(Figure *CurrentFigure, char Table[ROWS][COLS]);
Figure Rotate(Figure TempFigure);
void DeleteString(char Table[ROWS][COLS], int *score);  // checks lines
int isRoof(Figure shape);
void CreateFigure(Figure *CurrentFigure, char Table[ROWS][COLS], bool *GameOn);
void CheckPosition(int action, bool *GameOn, Figure *CurrentFigure,
                   char Table[ROWS][COLS], int *score, int *Stop,
                   Figure *TempFigure);
void InputUser(int action, bool *GameOn, Figure *CurrentFigure,
               char Table[ROWS][COLS], int *score, int *Stop, int maxScore);

#endif