#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "procedures.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "error: must supply only sudoku file\n");
		exit(1);
	}

	FILE *f = fopen(argv[1], "r");
	// do the magic
	uint16_t *rows = malloc(sizeof(uint16_t) * 9);
	uint16_t *cols = malloc(sizeof(uint16_t) * 9);
	uint16_t *squares= malloc(sizeof(uint16_t) * 9);
	read_board(f, rows, cols, squares);
	
	printf("\n");
	for (int i = 0; i < 9; i++) {
		printf("col %d: 0x%x\n", i, cols[i]);
		printf("row %d: 0x%x\n", i, rows[i]);
		printf("square  %d: 0x%x\n\n", i, squares[i]);
	}

	fclose(f);
	return 0;
}
