#ifndef MINICHESS_H_INCLUDED
#define MINICHESS_H_INCLUDED

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#define SIZE 5
#define INF 1000

/**
 * Run : g++ -O3 -std=c++14 -Wall test5.cpp
 */

class Node {
public:
	int _value;
	char _board[SIZE][SIZE];
	std::vector<std::unique_ptr<Node>> _next;

	Node () {
		//std::cout << "Allocation\n";
	};
	~Node () {/*std::cout << "Désallocation\n";*/};
};

void create_board (char board[SIZE][SIZE]);
void print_board (char board[SIZE][SIZE]);
void init_board (char board[SIZE][SIZE]);
void allocate_node (std::unique_ptr<Node>& tree, int number_move);
void initialized_next_nullptr (std::unique_ptr<Node>& tree);
void add_piece (char board[SIZE][SIZE], char piece, int row, int column);
int is_uppercase (char piece);
bool square_is_free (char board[SIZE][SIZE], int x, int y);
void copy_tab (std::unique_ptr<Node>& node_child, std::unique_ptr<Node>& parent);
bool is_ennemy (char board[SIZE][SIZE], int x, int y, bool turn);
int calculate_value_board (std::unique_ptr<Node>& tree);

int move_piece (std::unique_ptr<Node>& tree, char piece, int x, int y, int& number_move, bool& turn);
int bishop_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn);
int moves_bishop (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn);
int rook_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn);
int moves_rook (std::unique_ptr<Node>& tree, char piece, int x, int y, int& number_move, bool turn, int bool_verify_check);
void moves_queen (std::unique_ptr<Node>& tree, char piece, int x, int y, int& number_move, bool turn);
int knight_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn);
int moves_knight (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn);
int pawn_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn);
int moves_pawn (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn);
int king_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn);
int enemy_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn);
int moves_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn);

void select_piece (std::unique_ptr<Node>& tree, bool& turn);
int min (int a, int b);
int max (int a, int b);
int checkmate (std::unique_ptr<Node>& tree, int& number_move, bool& turn);
int alphabeta (std::unique_ptr<Node>& tree, int number_move, bool turn, int depth, int alpha, int beta);
void select_problem (std::unique_ptr<Node>& tree);

void print_node (std::unique_ptr<Node>& tree);
int main ();

#endif // MINICHESS_H_INCLUDED