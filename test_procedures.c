#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include "procedures.h"

Test(solve_read, read00)
{
	FILE *f = fopen("board.txt", "r");
	// do the magic
	uint16_t *rows = malloc(sizeof(uint16_t) * 9);
	uint16_t *cols = malloc(sizeof(uint16_t) * 9);
	uint16_t *squares= malloc(sizeof(uint16_t) * 9);
	read_board(f, rows, cols, squares);
	cr_assert(1 == 1);
	free(rows);
	free(cols);
	free(squares);
}
