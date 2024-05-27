.PHONY: clean

solve: solve.c
	clang -Wall -g -o solve solve.c procedures.c

test: test_procedures.c
	clang -o test -Wall procedures.c test_procedures.c -lm -lcriterion

clean:
	rm -r solve solve.dSYM test test.dSYM
