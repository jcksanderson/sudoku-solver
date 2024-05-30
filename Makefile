.PHONY: clean

solve: solve.c procedures.c
	clang -Wall -o solve procedures.c solve.c

fast: fast-solve.c procedures.c
	clang -Wall -o fast procedures.c fast-solve.c

test: test_procedures.c procedures.c
	clang -o test -Wall procedures.c test_procedures.c -lm -lcriterion

clean:
	rm -r solve solve.dSYM test test.dSYM
