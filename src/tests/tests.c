#include <assert.h>
#include <check.h>

#include "../brick_game/tetris/s21_tetris.h"
#include "../gui/cli/s21_gui_tetris.h"
// 1. CHECK
extern const Figure SamplesFigure[];

// 1. RULE
START_TEST(check_rule_s_test) {
  Figure figure = SamplesFigure[0];
  char table[ROWS][COLS] = {0};
  ck_assert_int_eq(CheckRuleS(figure, table), 1);
}
START_TEST(check_rule_d_test) {
  Figure figure = SamplesFigure[0];
  char table[ROWS][COLS] = {0};
  ck_assert_int_eq(CheckRuleD(table, figure), 1);
}
START_TEST(check_rule_d_test_2) {
  char Table[ROWS][COLS] = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  Figure figure = {.row = 0,
                   .col = 0,
                   .width = 3,
                   .samples = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}};
  ck_assert_int_eq(CheckRuleD(Table, figure), 0);
}
START_TEST(check_rule_a_test) {
  Figure figure = SamplesFigure[0];
  char table[ROWS][COLS] = {0};
  ck_assert_int_eq(CheckRuleA(table, figure), 1);
}
START_TEST(check_rule_w_test) {
  Figure figure = SamplesFigure[0];
  char table[ROWS][COLS] = {0};
  ck_assert_int_eq(CheckRuleW(table, figure), 1);
}

// 2.FILE
START_TEST(save_game_test) {
  int score = 200;
  int maxScore = 300;
  SaveGame(score, maxScore);
  int loaded_maxScore;
  LoadGame(&loaded_maxScore);
  ck_assert_int_eq(maxScore, loaded_maxScore);
}
START_TEST(load_game_test) {
  int score = 300;  // Исходное значение
  int loaded_score;
  LoadGame(&loaded_score);
  ck_assert_int_eq(score, loaded_score);
}
START_TEST(save_load_max_score_test) {
  int score = 300;
  int maxScore = 300;
  SaveGame(score, maxScore);
  int loaded_maxScore;
  LoadGame(&loaded_maxScore);
  ck_assert_int_eq(maxScore, loaded_maxScore);
}
START_TEST(save_load_game_test) {
  int score = 1500;
  int maxScore = 1500;
  SaveGame(score, maxScore);
  int loaded_score;
  LoadGame(&loaded_score);
  ck_assert_int_eq(score, loaded_score);
}
START_TEST(MaxScore_equal_score) {
  int score = 1500;
  int maxScore = 300;
  SaveGame(score, maxScore);
  int loaded_score;
  LoadGame(&loaded_score);
  ck_assert_int_eq(score, loaded_score);
}

// 3.ADDITIONAL
START_TEST(level_test) {
  int score = 1200;
  ck_assert_int_eq(level(score), 200000);
}
START_TEST(Rotate_test) {
  Figure figure = SamplesFigure[0];
  Figure rotated_figure = Rotate(figure);
  ck_assert_int_eq(rotated_figure.samples[0][1], figure.samples[1][0]);
  ck_assert_int_eq(rotated_figure.samples[1][0], figure.samples[0][1]);
}
START_TEST(DeleteString_test) {
  char table[ROWS][COLS] = {0};
  int score = 0;
  for (int i = 0; i < COLS; i++) {
    table[0][i] = 1;
  }
  DeleteString(table, &score);
  ck_assert_int_eq(score, 0);
  for (int i = 0; i < COLS; i++) {
    ck_assert_int_eq(table[0][i], 1);
  }
}

// 4.update_position
START_TEST(update_position_test) {
  Figure currentFigure = SamplesFigure[0];
  currentFigure.row = 0;
  currentFigure.col = 0;
  char buffer[ROWS][COLS] = {0};
  UpdatePosition(buffer, currentFigure);
  for (int i = 0; i < currentFigure.width; i++) {
    for (int j = 0; j < currentFigure.width; j++) {
      if (currentFigure.samples[i][j]) {
        ck_assert_int_eq(buffer[currentFigure.row + i][currentFigure.col + j],
                         1);
      } else {
        ck_assert_int_eq(buffer[currentFigure.row + i][currentFigure.col + j],
                         0);
      }
    }
  }
}

// 5.TABLE
START_TEST(write_to_table_test) {
  char table[ROWS][COLS] = {0};
  Figure current_figure = SamplesFigure[0];
  WriteToTable(&current_figure, table);
  for (int i = 0; i < current_figure.width; i++) {
    for (int j = 0; j < current_figure.width; j++) {
      if (current_figure.samples[i][j]) {
        ck_assert_int_eq(table[current_figure.row + i][current_figure.col + j],
                         1);
      } else {
        ck_assert_int_eq(table[current_figure.row + i][current_figure.col + j],
                         0);
      }
    }
  }
}

START_TEST(is_roof_test) {
  Figure roofFigure = {.width = 3, .row = 3, .col = 3};
  roofFigure.samples[0][0] = 1;
  roofFigure.samples[0][1] = 1;
  roofFigure.samples[0][2] = 1;
  roofFigure.samples[1][0] = 1;
  roofFigure.samples[1][1] = 1;
  roofFigure.samples[1][2] = 1;
  roofFigure.samples[2][0] = 1;
  roofFigure.samples[2][1] = 1;
  roofFigure.samples[2][2] = 1;

  ck_assert_int_eq(isRoof(roofFigure), TRUE);
}
END_TEST

// 6.FIGURE
START_TEST(CreateFigure_test_1) {
  Figure CurrentFigure = {0};
  char Table[ROWS][COLS] = {0};
  bool GameOn = true;

  CreateFigure(&CurrentFigure, Table, &GameOn);

  ck_assert_int_ne(CurrentFigure.row, -1);
  ck_assert_int_ne(CurrentFigure.col, 4);
  ck_assert_int_eq(GameOn, true);
}
START_TEST(CreateFigure_test_2) {
  Figure CurrentFigure = {0};
  char Table[ROWS][COLS] = {0};
  bool GameOn = true;

  CreateFigure(&CurrentFigure, Table, &GameOn);
  ck_assert_int_ne(CurrentFigure.row, -1);
  ck_assert_int_ne(CurrentFigure.col, 4);
}

// 6. CHECK

START_TEST(input_user_test_S) {
  char Table[ROWS][COLS] = {0};
  Figure CurrentFigure = SamplesFigure[0];
  Figure TempFigure = CurrentFigure;
  int score = 0;
  int Stop = 0;
  bool GameOn = true;
  char action = 's';
  CheckPosition(action, &GameOn, &CurrentFigure, Table, &score, &Stop,
                &TempFigure);
  ck_assert_int_ne(CurrentFigure.row, 1);
  ck_assert_int_ne(CurrentFigure.col, 4);
  ck_assert_int_eq(GameOn, true);
}

START_TEST(input_user_test_D) {
  char Table[ROWS][COLS] = {0};
  Figure CurrentFigure = SamplesFigure[0];
  Figure TempFigure = CurrentFigure;
  int score = 0;
  int Stop = 0;
  bool GameOn = true;
  char action = 'd';
  CheckPosition(action, &GameOn, &CurrentFigure, Table, &score, &Stop,
                &TempFigure);
  ck_assert_int_ne(CurrentFigure.row, -1);
  ck_assert_int_ne(CurrentFigure.col, 5);
  ck_assert_int_eq(GameOn, true);
}

START_TEST(input_user_test_A) {
  char Table[ROWS][COLS] = {0};
  Figure CurrentFigure = SamplesFigure[0];
  Figure TempFigure = CurrentFigure;
  int score = 0;
  int Stop = 0;
  bool GameOn = true;
  char action = 'a';
  CheckPosition(action, &GameOn, &CurrentFigure, Table, &score, &Stop,
                &TempFigure);
  ck_assert_int_ne(CurrentFigure.row, -1);
  ck_assert_int_ne(CurrentFigure.col, 3);
  ck_assert_int_eq(GameOn, true);
}

START_TEST(input_user_test_Space) {
  char Table[ROWS][COLS] = {0};
  Figure CurrentFigure = SamplesFigure[0];
  Figure TempFigure = CurrentFigure;
  int score = 0;
  int Stop = 0;
  bool GameOn = TRUE;
  char action = ' ';
  CheckPosition(action, &GameOn, &CurrentFigure, Table, &score, &Stop,
                &TempFigure);
  ck_assert_int_ne(CurrentFigure.row, -1);
  ck_assert_int_ne(CurrentFigure.col, 4);
  ck_assert_int_eq(Stop, 1);
}

START_TEST(input_user_test_W) {
  Figure figure = SamplesFigure[0];
  char table[ROWS][COLS] = {0};
  bool gameOn = TRUE;
  int score = 0;
  int stopFlag = 0;
  Figure tempFigure = {0};

  CheckPosition('w', &gameOn, &figure, table, &score, &stopFlag, &tempFigure);
  ck_assert_int_eq(CheckRuleW(table, Rotate(figure)), 1);
}
END_TEST
START_TEST(input_user_test_O) {
  Figure figure = SamplesFigure[0];
  char table[ROWS][COLS] = {0};
  bool gameOn = TRUE;
  int score = 0;
  int stopFlag = 0;
  Figure tempFigure = {0};

  CheckPosition('o', &gameOn, &figure, table, &score, &stopFlag, &tempFigure);
  ck_assert_int_eq(gameOn, FALSE);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("tetris_check");
  TCase *tc1_1 = tcase_create("tetris_check");
  SRunner *sr = srunner_create(s1);

  int nf;

  suite_add_tcase(s1, tc1_1);
  // 1. CHECK
  tcase_add_test(tc1_1, check_rule_s_test);
  tcase_add_test(tc1_1, check_rule_d_test);
  tcase_add_test(tc1_1, check_rule_d_test_2);
  tcase_add_test(tc1_1, check_rule_a_test);
  tcase_add_test(tc1_1, check_rule_w_test);

  // 2.FILE
  tcase_add_test(tc1_1, save_game_test);
  tcase_add_test(tc1_1, load_game_test);
  tcase_add_test(tc1_1, save_load_max_score_test);
  tcase_add_test(tc1_1, save_load_game_test);
  tcase_add_test(tc1_1, MaxScore_equal_score);

  // 3.ADDITIONAL
  tcase_add_test(tc1_1, level_test);
  tcase_add_test(tc1_1, Rotate_test);
  tcase_add_test(tc1_1, DeleteString_test);

  // 4.update_position
  tcase_add_test(tc1_1, (update_position_test));

  // 5.TABLE
  tcase_add_test(tc1_1, write_to_table_test);
  tcase_add_test(tc1_1, is_roof_test);

  // 6.FIGURE
  tcase_add_test(tc1_1, CreateFigure_test_1);
  tcase_add_test(tc1_1, CreateFigure_test_2);

  // 7. CHECK POSITION
  tcase_add_test(tc1_1, input_user_test_S);
  tcase_add_test(tc1_1, input_user_test_D);
  tcase_add_test(tc1_1, input_user_test_A);
  tcase_add_test(tc1_1, input_user_test_W);
  tcase_add_test(tc1_1, input_user_test_O);
  tcase_add_test(tc1_1, input_user_test_Space);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}