.PHONY: clean

solve: solve.c
	clang -Wall -g -o solve solve.c

test: test_solve.c
	clang -o test -Wall solve.c test_solve.c -lm -lcriterion

clean:
	rm -r solve solve.dSYM test test.dSYM
