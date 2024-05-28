#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct sudoku_game {
	uint16_t *rows;
	uint16_t *cols;
	uint16_t *squares;
	uint8_t **board;
};
typedef struct sudoku_game sudoku_game;

void read_board(FILE *f, sudoku_game game);

uint8_t *generate_options(uint16_t possible, uint8_t *len);
