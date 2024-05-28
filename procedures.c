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

void read_board(FILE *f, sudoku_game game)
{
	int num;
	int idx = 0;
	while ((num = getc(f)) != EOF) {
		if (num == '\n') continue;
		// fprintf(stderr, "read number: %c\n", (char)num);
		uint16_t bit = number_bit(num);
		game.rows[idx / 9] += bit;
		game.cols[idx % 9] += bit;
		game.squares[3 * (idx / 27) + 
						((idx / 3) - (3 * (idx / 9)))] += bit;
		game.board[idx / 9][idx % 9] = num - 48;
		idx++;
	}
}

// have to figure out how to do this brute force technique
// write function for determining the possible values at a square
// iterate through those values
// go to the next open square, determine the possible values
// iterate through those values
// etc.

// right now the problem is how exactly i find out if a value doesn't work

uint8_t *generate_options(uint16_t possible, uint8_t *len)
{
	for (char i = '1'; i <= '9'; i++) {
		if (possible & number_bit(i)) (*len)++;
	}
	if (!len) return NULL;
	
	uint8_t *opts = malloc(sizeof(uint8_t) * (*len));
	int idx = 0;
	for (char i = '1'; i <= '9'; i++) {
		if (possible & number_bit(i)) {
			opts[idx] = i - 48;
			idx++;
		}
	}
	return opts;
}

// assumes that row, col is not already filled
int solve_board(sudoku_game game)
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			// skip if already filled
			if (game.board[i][j] != 0) continue;
			// calculate the "inner square"
			int sqr = 3 * (i/3) + (j/3);
			uint16_t possible = (0x1FF & ~(game.rows[i] | game.cols[j] | 
														game.squares[sqr]));

			fprintf(stderr, "checking pos (%d, %d) sqr: %d\n", i, j, sqr);
			fprintf(stderr, "possible num: 0x%x\n", possible);

			uint8_t len = 0;
			uint8_t *opts = generate_options(possible, &len);
			fprintf(stderr, "possible vals: %d\n", len);

			uint16_t row_bkp = game.rows[i];
			uint16_t col_bkp = game.cols[j];
			uint16_t sqr_bkp = game.squares[sqr];

			// iterate through options
			for (int k = 0; k < len; k++) {
				fprintf(stderr, "Loc: (%d, %d) | Opt: %d\n\n", i, j, opts[k]);

				game.board[i][j] = opts[k];
				game.rows[i] += number_bit(opts[k] + 48); 
				game.cols[j] += number_bit(opts[k] + 48);	
				game.squares[sqr] += number_bit(opts[k] + 48);

				int status = solve_board(game);

				if (!status) {
					game.rows[i] = row_bkp;
					game.cols[j] = col_bkp;
					game.squares[sqr] = sqr_bkp;
					continue;
				}
				return 1;
			}
			// if we iterated through all options and didn't succeed
			// or if no options, we failed (return 0, reset position)
			game.board[i][j] = 0;
			return 0;
		}
	}
	// if we've dealt with the full board, success
	return 1;
}

