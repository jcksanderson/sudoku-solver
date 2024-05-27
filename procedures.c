#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "procedures.h"

uint16_t number_bit(char num)
{
	switch (num) {
		case '0':
			return 0;
		case '1':
			return 0x1;
		case '2':
			return 0x2;
		case '3':
			return 0x4;
		case '4':
			return 0x8;
		case '5':
			return 0x10;
		case '6':
			return 0x20;
		case '7':
			return 0x40;
		case '8':
			return 0x80;
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
		// fprintf(stderr, "read number: %c\n", (char)num);
		uint16_t bit = number_bit(num);
		rows[idx / 9] += bit;
		cols[idx % 9] += bit;
		squares[3 * (idx / 27) + 
						((idx / 3) - (3 * (idx / 9)))] += bit;
		idx++;
	}
}

