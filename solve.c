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
	sudoku_game game_2;
	sudoku_game game_3;
	// initialize game arrays
	game_1.rows = malloc(sizeof(uint16_t) * 9);
	game_1.cols = malloc(sizeof(uint16_t) * 9);
	game_1.squares = malloc(sizeof(uint16_t) * 9);
	game_1.board = malloc(sizeof(uint8_t *) * 9);
	for (int i = 0; i < 9; i++) {
		game_1.board[i] = malloc(sizeof(uint8_t) * 9);
	}
	game_2.rows = malloc(sizeof(uint16_t) * 9);
	game_2.cols = malloc(sizeof(uint16_t) * 9);
	game_2.squares = malloc(sizeof(uint16_t) * 9);
	game_2.board = malloc(sizeof(uint8_t *) * 9);
	for (int i = 0; i < 9; i++) {
		game_2.board[i] = malloc(sizeof(uint8_t) * 9);
	}
	game_3.rows = malloc(sizeof(uint16_t) * 9);
	game_3.cols = malloc(sizeof(uint16_t) * 9);
	game_3.squares = malloc(sizeof(uint16_t) * 9);
	game_3.board = malloc(sizeof(uint8_t *) * 9);
	for (int i = 0; i < 9; i++) {
		game_3.board[i] = malloc(sizeof(uint8_t) * 9);
	}


	read_board(f, game_1);
	// reset the file pointer
	rewind(f);
	read_board(f, game_2);
	rewind(f);
	read_board(f, game_3);
	fclose(f);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d", game_3.board[i][j]); 
		}
		printf("\n");
	}


	struct timeval start_1;
	struct timeval stop_1;
	struct timeval start_2;
	struct timeval stop_2;
	struct timeval start_3;
	struct timeval stop_3;

	// time slow solve
	gettimeofday(&start_1, NULL);
	solve_board(game_1);
	gettimeofday(&stop_1, NULL);

	unsigned long int t0 = start_1.tv_sec * 1000000 + start_1.tv_usec;
	unsigned long int t1 = stop_1.tv_sec * 1000000 + stop_1.tv_usec;
	fprintf(stderr, "slow solving time (usec): %lu\n", t1-t0);

	// time fast solve
	gettimeofday(&start_2, NULL);
	solve_board_fast(game_2, 0, 0);
	gettimeofday(&stop_2, NULL);

	unsigned long int t2 = start_2.tv_sec * 1000000 + start_2.tv_usec;
	unsigned long int t3 = stop_2.tv_sec * 1000000 + stop_2.tv_usec;
	fprintf(stderr, "fast solving time (usec): %lu\n", t3-t2);

	// time fast solve
	gettimeofday(&start_3, NULL);
	solve_board_fastest(game_3);
	gettimeofday(&stop_3, NULL);

	unsigned long int t4 = start_3.tv_sec * 1000000 + start_3.tv_usec;
	unsigned long int t5 = stop_3.tv_sec * 1000000 + stop_3.tv_usec;
	fprintf(stderr, "fastest solving time (usec): %lu\n", t5-t4);


	// print results
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d", game_1.board[i][j]); 
		}
		printf("\n");
	}
	printf("---------\n");

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d", game_2.board[i][j]); 
		}
		printf("\n");
	}
	printf("---------\n");

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d", game_3.board[i][j]); 
		}
		printf("\n");
	}

	// See about a 50 microsecond speedup on average with the fast solve

	return 0;
}
