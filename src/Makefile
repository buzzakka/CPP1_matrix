FLAGS = -Wall -Werror -Wextra
FLAG_C17 = -std=c++17
ALL_OBJS = *.cc *.h
LIB_OBJ = s21_matrix_oop.cc s21_other.cc
TEST_OBJ = test.cc
CLANG_PATH = ../clang/

all: clean style test s21_matrix_oop.a

s21_matrix_oop.a: clean
	g++ $(FLAGS) $(FLAG_C17) $(LIB_OBJ) -c
	ar rc lib_s21_matrix_oop.a *.o
	rm -rf *.o

clean:
	rm -rf *.o *.a *.exe s21_matrix_oop test .clang-format

test: clean
	g++ $(FLAG_C17) $(TEST_OBJ) $(LIB_OBJ) -o test -lgtest -pthread && ./test

style:
	cd $(CLANG_PATH) && cp .clang-format ../src/
	clang-format -n $(ALL_OBJS)
	rm -rf .clang-format