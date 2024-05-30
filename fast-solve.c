#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include "procedures.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "error: must supply only sudoku file\n");
		exit(1);
	}

	// open file
	FILE *f = fopen(argv[1], "r");
	sudoku_game game_1;
	// initialize game arrays
	game_1.rows = malloc(sizeof(uint16_t) * 9);
	game_1.cols = malloc(sizeof(uint16_t) * 9);
	game_1.squares = malloc(sizeof(uint16_t) * 9);
	game_1.board = malloc(sizeof(uint8_t *) * 9);
	for (int i = 0; i < 9; i++) {
		game_1.board[i] = malloc(sizeof(uint8_t) * 9);
	}
	

	read_board(f, game_1);
	fclose(f);

	printf("Unsolved board:\n");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d", game_1.board[i][j]); 
		}
		printf("\n");
	}


	struct timeval start_1;
	struct timeval stop_1;
	
	// time slow solve
	gettimeofday(&start_1, NULL);
	solve_board_fastest(game_1);
	gettimeofday(&stop_1, NULL);

	unsigned long int t0 = start_1.tv_sec * 1000000 + start_1.tv_usec;
	unsigned long int t1 = stop_1.tv_sec * 1000000 + stop_1.tv_usec;
	fprintf(stderr, "solving time (usec): %lu\n", t1-t0);

	// print result
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d", game_1.board[i][j]); 
		}
		printf("\n");
	}

	// See about a 50 microsecond speedup on average with the fast solve

	return 0;
}
