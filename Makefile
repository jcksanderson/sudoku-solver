.PHONY: clean

solve: sudoku_solve.c
	clang -Wall -g -o solve sudoku_solve.c
