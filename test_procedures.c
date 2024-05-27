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

	uint16_t row_exp[] = {0x26, 0x115, 0xA9, 0x183, 0xC0, 0xE2, 
												0x132, 0x186, 0x15};
	uint16_t col_exp[] = {0x1C0, 0x0, 0xB7, 0xE7, 0x3, 0x1B6, 0x13E, 
												0x0, 0x181};
	uint16_t sqr_exp[] = {0x105, 0xB6, 0x29, 0xE0, 0xC3, 0x182,
												0x92, 0x127, 0x114};

	for (int i = 0; i < 9; i++) {
		cr_assert(rows[i] == row_exp[i]);
		cr_assert(cols[i] == col_exp[i]);
		cr_assert(squares[i] == sqr_exp[i]);
	}

	free(rows);
	free(cols);
	free(squares);
}
