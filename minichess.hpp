#ifndef MINICHESS_H_INCLUDED
#define MINICHESS_H_INCLUDED

#include <iostream>
#include <vector>
#define SIZE 5

using namespace std;

class Piece {
public:
	Piece (char piece, int x, int y);
	~Piece ();

	char get_piece ();
	void set_piece (char piece);
	int get_x ();
	void set_x (int x);
	int get_y ();
	void set_y (int y);

private:
	char _piece;
	int _x;
	int _y;
};

class Minichess {
public:
	char _board[SIZE][SIZE];
	bool _turn;

	void create_board ();
	void init_board ();
	void print_board ();
	void add_piece (char piece, int row, int column);
	bool is_ennemy(char piece, int x, int y);

	int rook_attacks (int x, int y);
	void moves_rook (int x, int y);

	int pawn_attacks (int x, int y);
	void moves_pawn (int x, int y);
	bool square_is_free(int x, int y);
	bool is_uppercase (char piece);
	void select_piece ();
	void playout ();
	void number_piece (std::vector<Piece> &v);
};

#endif // MINICHESS_H_INCLUDED