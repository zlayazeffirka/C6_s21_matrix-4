DATE = $(shell date -R)
CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 
DB = -g -O0
OBJ = obj
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c, $(OBJDIR)%.o, $(SOURCES))
TEST = s21_test
NAME = s21_matrix

OS := $(shell uname)
# UBUNTU := $(shell hostnamectl | grep -o 'Ubuntu')
MAC_X86 := $(shell uname -a | grep -o _X86_64)
MAC_M1 := $(shell uname -a | grep -o _ARM64)

ifeq ($(OS), Linux)
	TEST_LIBS = -lcheck -pthread -lrt -lm -lsubunit
	MATH = -lm
	OPEN = xdg-open
else ifeq ($(UBUNTU), Ubuntu)
	TEST_FLAGS=-lpthread -lcheck  -Wno-nonnull -Wno-memset-transposed-args -lm -lsubunit
	OPEN = open
endif

ifeq ($(MAC_M1), _ARM64)
	TEST_LIBS := -I/opt/homebrew/opt/check/include -L/opt/homebrew/opt/check/lib -lcheck
	OPEN = open
endif
ifeq ($(MAC_X86), _X86_64)
	TEST_LIBS = $(shell pkg-config --libs --cflags check) -lm
	OPEN = open
endif

all: $(NAME).a

build: all

repo:
	mkdir -p $(OBJ)
$(OBJDIR)%.o: %.c
	$(CC) $(FLAGS) -c $< -o obj/$@

db: fix clean reset 
	$(CC) $(FLAGS) $(DB) s21_arithmetic.c secondary_functions.c test_db/test.c -o $(TEST) $(MATH)
	./$(TEST)
dbf: fix clean reset
	$(CC) $(FLAGS) $(DB) s21_arithmetic.c s21_bits.c s21_comparison.c s21_converters.c s21_normalize.c s21_other.c test_db/test.c -o $(TEST) $(MATH)
	./$(TEST) > 1.txt

$(NAME).a: repo $(OBJECTS)
	ar rcs $(NAME).a $(OBJ)/*.o
	ranlib $(NAME).a
	
test: reset $(NAME).a 
	$(CC) $(FLAGS) test_s21/*.c *.c $(NAME).a $(TEST_LIBS) -o s21_test
	./$(TEST)

# main: reset $(NAME).a 
# 	$(CC) $(FLAGS) main.c *.c $(NAME).a -o s21_main
# 	./s21_main

gcov_flag:
	$(eval FLAGS += --coverage)
gcov_report: clean gcov_flag test
	mkdir -p report
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory report
	rm -rf *.gcno *.gcda *.gcov *.info
	$(OPEN) report/index.html

brew:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	reset
	brew install lcov
	brew install check
	brew install pkg-config
	sleep 1
	reset

fix:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n *.c *.h test_s21/*.c test_s21/*.h 
	clang-format -i *.c *.h test_s21/*.c test_s21/*.h 
	sleep 1
	reset
	clang-format -n *.c *.h test_s21/*.c test_s21/*.h 

add_db_flag:
	$(eval FLAGS += $(DB))
mem: clean add_db_flag test
ifeq ($(OS),Linux)
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(TEST)
else
	leaks --atExit -- ./$(TEST)
endif

cpp: reset
	cppcheck --enable=all --suppress=missingIncludeSystem ./*.c *.h ./test_s21/*.c ./test_s21/*.h

rebuild: clean build
	
clean:
	rm -rf $(TEST) *.o *.a *.gcno *.gcda *.gcov *.info report a.out *.dSYM obj
	reset

reset:
	reset | bash