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
	sudoku_game game;
	game.rows = malloc(sizeof(uint16_t) * 9);
	game.cols = malloc(sizeof(uint16_t) * 9);
	game.squares = malloc(sizeof(uint16_t) * 9);
	game.board = malloc(sizeof(uint8_t *) * 9);
	for (int i = 0; i < 9; i++) {
		game.board[i] = malloc(sizeof(uint8_t) * 9);
	}

	read_board(f, game);
	fclose(f);

	solve_board(game);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d", game.board[i][j]); 
		}
		printf("\n");
	}
	return 0;
}
