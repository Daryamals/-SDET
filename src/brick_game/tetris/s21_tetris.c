#include "s21_tetris.h"

const Figure SamplesFigure[] = {{.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 1, 1, 1, 1},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},

                                {.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 1, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},

                                {.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 1, 0, 0, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},

                                {.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},

                                {.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},
                                {.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},
                                {.samples =
                                     {
                                         {0, 0, 0, 0},
                                         {0, 1, 1, 0},
                                         {0, 1, 1, 0},
                                         {0, 0, 0, 0},
                                     },
                                 .width = 4,
                                 .row = 0,
                                 .col = 0}};

Figure CaptureFigure(Figure figure) { return figure; }

void LoadGame(int *score) {
  FILE *file = fopen("savegame.txt", "r");
  if (file != NULL) {
    fscanf(file, "%d", score);
    fclose(file);
  }
}

void SaveGame(int score, int maxScore) {
  FILE *file = fopen("savegame.txt", "w");
  if (file != NULL) {
    if (maxScore < score) {
      maxScore = score;
    }
    fprintf(file, "%d", maxScore);
    fclose(file);
  }
}

void UpdatePosition(char Buffer[ROWS][COLS], Figure CurrentFigure) {
  for (int i = 0; i < CurrentFigure.width; i++) {
    for (int j = 0; j < CurrentFigure.width; j++) {
      if (CurrentFigure.samples[i][j] && CurrentFigure.row + i < 20 &&
          CurrentFigure.col + j < 10) {
        Buffer[CurrentFigure.row + i][CurrentFigure.col + j] =
            CurrentFigure.samples[i][j];
      }
    }
  }
  clear();
  refresh();
}

void PrintTable(char Table[ROWS][COLS], int *score, Figure CurrentFigure,
                int maxScore) {
  char Buffer[ROWS][COLS] = {0};
  UpdatePosition(Buffer, CurrentFigure);
  PrintColor(Table, Buffer);
  AdditionalInformation(*score, maxScore);
  refresh();
}

int CheckRuleS(Figure TempFigure, char Table[ROWS][COLS]) {
  int flag = 1;  // okv
  for (int i = 0; i < TempFigure.width; i++) {
    for (int j = 0; j < TempFigure.width; j++) {
      if (Table[TempFigure.row + i + 1][TempFigure.col + j] &&
          TempFigure.samples[i][j])
        flag = 0;
    }
  }
  return flag;
}
int CheckRuleD(char Table[ROWS][COLS], Figure figure) {
  int flag = 1;  // ok

  for (int i = 0; i < figure.width; i++) {
    for (int j = 0; j < figure.width; j++) {
      if (figure.col + j >= COLS - 1 || figure.row + 1 > ROWS - 1) {
        if (figure.samples[i][j]) flag = 0;
      } else if (Table[figure.row + i + 1][figure.col + j + 1] &&
                 figure.samples[i][j])
        flag = 0;
    }
  }
  return flag;
}
int CheckRuleA(char Table[ROWS][COLS], Figure figure) {
  int flag = 1;  // ok
  for (int i = 0; i < figure.width; i++) {
    for (int j = 0; j < figure.width; j++) {
      if (figure.col + j <= 0 || figure.col + j - 1 >= COLS ||
          figure.row + i >= ROWS) {
        if (figure.samples[i][j]) flag = 0;
      } else if (Table[figure.row + i + 1][figure.col + j - 1] &&
                 figure.samples[i][j])
        flag = 0;
    }
  }
  return flag;
}

int CheckRuleW(char Table[ROWS][COLS], Figure figure) {
  int flag = 1;  // ok
  for (int i = 0; i < figure.width; i++) {
    for (int j = 0; j < figure.width; j++) {
      if (figure.col + j <= 0 || figure.row >= ROWS || figure.col + j > COLS ||
          figure.col + j >= COLS) {
        if (figure.samples[i][j]) flag = 0;
      } else if (Table[figure.row + i + 1][figure.col + j] &&
                 figure.samples[i][j])
        flag = 0;
    }
  }
  return flag;
}

void WriteToTable(Figure *CurrentFigure, char Table[ROWS][COLS]) {
  for (int i = 0; i < CurrentFigure->width; i++) {
    for (int j = 0; j < CurrentFigure->width; j++) {
      if (CurrentFigure->samples[i][j])
        Table[CurrentFigure->row + i][CurrentFigure->col + j] =
            CurrentFigure->samples[i][j];
    }
  }
}

Figure Rotate(Figure TempFigure) {
  Figure temp = CaptureFigure(TempFigure);
  for (int i = 0; i < TempFigure.width; i++) {
    for (int j = 0, k = TempFigure.width - 1; j < TempFigure.width; j++, k--) {
      TempFigure.samples[i][j] = temp.samples[k][i];
    }
  }
  return TempFigure;
}

void DeleteString(char Table[ROWS][COLS], int *score) {
  int sum, count = 0, temp_score = 0;
  for (int i = 1; i < ROWS - 1; i++) {
    sum = 0;
    for (int j = 1; j < COLS; j++) {
      sum += Table[i][j];
    }
    if (sum == COLS + 1) {
      count++;
      int k;
      for (k = i; k >= 2; k--)
        for (int l = 1; l < COLS - 1; l++) Table[k][l] = Table[k - 1][l];

      for (int l = 1; l < COLS - 1; l++) Table[k][l] = 0;
      while (count) {
        temp_score = temp_score * 2 + 100;
        count--;
      }
    }
  }
  (*score) = (*score) + temp_score;
}

int isRoof(Figure shape) {
  for (int i = 0; i < shape.width; i++) {
    for (int j = 0; j < shape.width; j++) {
      if (shape.samples[i][j]) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

void CreateFigure(Figure *CurrentFigure, char Table[ROWS][COLS], bool *GameOn) {
  WriteToTable(CurrentFigure, Table);
  Figure NewFigure = SamplesFigure[rand() % 7];
  NewFigure.row = 0;
  NewFigure.col = COLS / 4 + 1;
  *CurrentFigure = NewFigure;
  if (!CheckRuleS(*CurrentFigure, Table) && CurrentFigure->row == 0) {
    (*GameOn) = false;
  }
}

void CheckPosition(int action, bool *GameOn, Figure *CurrentFigure,
                   char Table[ROWS][COLS], int *score, int *Stop,
                   Figure *TempFigure) {
  switch (action) {
    case 's':
      if (!(*Stop)) {
        *TempFigure = *CurrentFigure;

        if (CheckRuleS(*TempFigure, Table)) {
          TempFigure->row++;
        } else {
          CreateFigure(CurrentFigure, Table, GameOn);
          DeleteString(Table, score);
          *TempFigure = *CurrentFigure;
        }
      }
      break;
    case 'd':
      if (CheckRuleD(Table, *TempFigure) && !(*Stop)) {
        TempFigure->col++;
      }
      break;
    case 'a':
      if (CheckRuleA(Table, *TempFigure) && !(*Stop)) {
        TempFigure->col--;
      }
      break;
    case 'w':
      if (CheckRuleW(Table, Rotate(*TempFigure)) && !(*Stop) &&
          TempFigure->row >= 0) {
        *TempFigure = Rotate(*TempFigure);
      }
      break;
    case ' ':
      *Stop = !(*Stop);
      break;
    case 'o':
      (*GameOn) = FALSE;
      break;
  }
}

void InputUser(int action, bool *GameOn, Figure *CurrentFigure,
               char Table[ROWS][COLS], int *score, int *Stop, int maxScore) {
  Figure TempFigure = *CurrentFigure;
  CheckPosition(action, GameOn, CurrentFigure, Table, score, Stop, &TempFigure);
  *CurrentFigure = TempFigure;
  PrintTable(Table, score, *CurrentFigure, maxScore);
}

int level(int score) {
  int count = 0;
  int level_up = 0;
  if (count <= 10) {
    level_up = (score / 600) * 100000;
    count++;
  }

  return level_up;
}