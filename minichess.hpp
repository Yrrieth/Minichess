#ifndef MINICHESS_H_INCLUDED
#define MINICHESS_H_INCLUDED

#include <iostream>
#define SIZE 5

using namespace std;

class Minichess {
public:
	char _board[SIZE][SIZE];
	bool _turn;

	void create_board ();
	void init_board ();
	void print_board ();
	void add_piece (char piece, int row, int column);
	int pawn_attacks (int x, int y);
	void moves_pawn (int x, int y);
	bool is_free(int x, int y);
	bool is_uppercase (char piece);
	void select_piece ();
	void playout ();
};

int test();

#endif // MINICHESS_H_INCLUDED