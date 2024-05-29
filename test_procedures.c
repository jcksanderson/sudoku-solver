#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include "procedures.h"

// ===== Read Board Tests =====

Test(procedures_read, read00)
{
	FILE *f = fopen("boards/board-1.txt", "r");
	sudoku_game game;

	game.rows = malloc(sizeof(uint16_t) * 9);
	game.cols = malloc(sizeof(uint16_t) * 9);
	game.squares= malloc(sizeof(uint16_t) * 9);
	game.board = malloc(sizeof(uint8_t *) * 9);
	for (int i = 0; i < 9; i++) {
		game.board[i] = malloc(sizeof(uint8_t) * 9);
	}
	read_board(f, game);

	uint16_t row_exp[] = {0x26, 0x115, 0xA9, 0x183, 0xC0, 0xE2, 
												0x132, 0x186, 0x15};
	uint16_t col_exp[] = {0x1C0, 0x0, 0xB7, 0xE7, 0x3, 0x1B6, 0x13E, 
												0x0, 0x181};
	uint16_t sqr_exp[] = {0x105, 0xB6, 0x29, 0xE0, 0xC3, 0x182,
												0x92, 0x127, 0x114};
	char board_exp[9][9] = {
		{0,0,3,0,2,0,6,0,0},
		{9,0,0,3,0,5,0,0,1},
		{0,0,1,8,0,6,4,0,0},
		{0,0,8,1,0,2,9,0,0},
		{7,0,0,0,0,0,0,0,8},
		{0,0,6,7,0,8,2,0,0},
		{0,0,2,6,0,9,5,0,0},
		{8,0,0,2,0,3,0,0,9},
		{0,0,5,0,1,0,3,0,0}
	};

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cr_assert(board_exp[i][j] == game.board[i][j]);
		}
		cr_assert(game.rows[i] == row_exp[i]);
		cr_assert(game.cols[i] == col_exp[i]);
		cr_assert(game.squares[i] == sqr_exp[i]);
	}
	
	free_game(game);
}


// ===== Possible Value Generation =====

Test(procedures_gen, gen00)
{
	uint16_t possible = 0x1FF;
	uint8_t len;
	uint8_t *opts = generate_options(possible, &len);
	cr_assert(len == 9);
	uint8_t exp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (int i = 0; i < len; i++) {
		cr_assert(opts[i] == exp[i]);
	}
	free(opts);
}

Test(procedures_gen, gen01)
{
	uint16_t possible = 0x19A;
	uint8_t len;
	uint8_t *opts = generate_options(possible, &len);
	cr_assert(len == 5);
	uint8_t exp[] = {2, 4, 5, 8, 9};
	for (int i = 0; i < len; i++) {
		cr_assert(opts[i] == exp[i]);
	}
	free(opts);
}

// ===== Board Solving =====

Test(procedures_solve, solve00)
{
	FILE *f = fopen("boards/board-1.txt", "r");
	sudoku_game game;

	game.rows = malloc(sizeof(uint16_t) * 9);
	game.cols = malloc(sizeof(uint16_t) * 9);
	game.squares= malloc(sizeof(uint16_t) * 9);
	game.board = malloc(sizeof(uint8_t *) * 9);
	for (int i = 0; i < 9; i++) {
		game.board[i] = malloc(sizeof(uint8_t) * 9);
	}
	read_board(f, game);

	solve_board(game);

	uint8_t solved_board[9][9] = {
		{4, 8, 3, 9, 2, 1, 6, 5, 7},
		{9, 6, 7, 3, 4, 5, 8, 2, 1},
		{2, 5, 1, 8, 7, 6, 4, 9, 3},
		{5, 4, 8, 1, 3, 2, 9, 7, 6},
		{7, 2, 9, 5, 6, 4, 1, 3, 8},
		{1, 3, 6, 7, 9, 8, 2, 4, 5},
		{3, 7, 2, 6, 8, 9, 5, 1, 4},
		{8, 1, 4, 2, 5, 3, 7, 6, 9},
		{6, 9, 5, 4, 1, 7, 3, 8, 2}
	};
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cr_assert(game.board[i][j] == solved_board[i][j]);
		}
	}
	free_game(game);
}

Test(procedures_solve, solve01)
{
	FILE *f = fopen("boards/board-2.txt", "r");
	sudoku_game game;

	game.rows = malloc(sizeof(uint16_t) * 9);
	game.cols = malloc(sizeof(uint16_t) * 9);
	game.squares= malloc(sizeof(uint16_t) * 9);
	game.board = malloc(sizeof(uint8_t *) * 9);
	for (int i = 0; i < 9; i++) {
		game.board[i] = malloc(sizeof(uint8_t) * 9);
	}

	read_board(f, game);
	solve_board(game);

	uint8_t solved_board[9][9] = {
		{2,4,5,9,8,1,3,7,6},
		{1,6,9,2,7,3,5,8,4},
		{8,3,7,5,6,4,2,1,9},
		{9,7,6,1,2,5,4,3,8},
		{5,1,3,4,9,8,6,2,7},
		{4,8,2,7,3,6,9,5,1},
		{3,9,1,6,5,7,8,4,2},
		{7,2,8,3,4,9,1,6,5},
		{6,5,4,8,1,2,7,9,3}
	};
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cr_assert(game.board[i][j] == solved_board[i][j]);
		}
	}
	free_game(game);
}
