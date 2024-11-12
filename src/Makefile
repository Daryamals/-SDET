OS = $(shell uname)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -O2 -Wall -Wextra -Werror -std=c11
TEST_FLAGS = -lgtest -lpthread -fprofile-arcs -ftest-coverage
FRONT_FLAGS = -lncurses
BRICK_FILES := $(wildcard brick_game/tetris/s21_*.c brick_game/tetris/main_tetris.c)
BRICK_FILES_FOR_TEST := $(wildcard brick_game/tetris/s21_*.c)
GUI_FILES := gui/cli/s21_gui_tetris.c
TEST_FILES := $(wildcard tests/tests.c)
SOURCE = $(BRICK_FILES) $(GUI_FILES)
OBJECTS = $(SOURCE:s21*.c=.o)
TEST_OBJECTS = $(TEST_FILES:.c=.o)
FRONT_FLAGS = -lncurses

ifeq ($(OS),Darwin)
    OPEN_CMD = open
    TEST_FLAGS += -lcheck -lm -lpthread -D_GNU_SOURCE
else
    TEST_FLAGS += -lm -lsubunit
    OPEN_CMD = xdg-open
endif

all: clean s21_tetris

s21_tetris: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(FRONT_FLAGS)

src/brick_game/tetris/%.o: src/brick_game/tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/gui/cli/%.o: src/gui/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/tests/%.o: src/tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: clean $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(TEST_FLAGS) $(BRICK_FILES_FOR_TEST) $(GUI_FILES) $(FRONT_FLAGS) $(TEST_FILES) -lgcov -coverage -o test
	./test

gcov_report: clean test
	lcov -t "./test" -o report.info --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

	rm -rf *.gcno *.gcda *.gco
leaks: test
	CK_FORK=no leaks --atExit -- ./test

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./test
	valgrind -s --tool=memcheck --leak-check=yes ./test	


clean:
	rm -rf $(shell find . -name "*.o") *.a s21_tetris test *.gcda *.gcno *.info report tetris.tar.gz

install: all
	@echo "Installing..."

uninstall: clean
	@echo "Uninstalling..."

dvi:
	$(OPEN_CMD) README.md

dist: clean all
	cd .. && tar -czvf src/tetris.tar.gz src

style:
	clang-format --style=Google -i $(shell find . -name "*.c" -o -name "*.h")
	clang-format --style=Google -n $(shell find . -name "*.c" -o -name "*.h")

.PHONY: all clean install uninstall dvi dist test gcov_report clang
