#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "solve.h"

uint16_t number_bit(char num)
{
	switch (num) {
		case '0':
			return 0;
		case '1':
			return 0x001;
		case '2':
			return 0x002;
		case '3':
			return 0x004;
		case '4':
			return 0x008;
		case '5':
			return 0x010;
		case '6':
			return 0x020;
		case '7':
			return 0x040;
		case '8':
			return 0x080;
		case '9':
			return 0x100;
		default:
			fprintf(stderr, "number bit: must be between 0 and 9\n");
			exit(1);
	}
}


void read_board(FILE *f, uint16_t *rows, uint16_t *cols, uint16_t *squares)
{
	int num;
	int idx = 0;
	while ((num = getc(f)) != EOF) {
		if (num == '\n') continue;
		uint16_t bit = number_bit(num);
		rows[idx / 9] += bit;
		cols[idx % 9] += bit;
		squares[(idx / 27) + 
						((idx / 3) - (idx / 9))] += bit;
		idx++;
		num = getc(f);
	}
}

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
