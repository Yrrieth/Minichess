#include <iostream>
#include <array>
#define SIZE 5

using namespace std;

class Minichess {
public:
	char board [SIZE][SIZE];

	void create_board (char board[SIZE][SIZE]) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				board[i][j] = '.';
			}
		}
	}

	void init_board (char board[SIZE][SIZE]) {
		char white_valuable_piece[SIZE] = {'R', 'B', 'N', 'Q', 'K'};
		char black_valuable_piece[SIZE] = {'r', 'b', 'n', 'q', 'k'};

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (i == 0) {
					board[i][j] = black_valuable_piece[j];
				}
				if (i == 1) { // Black pawns
					board[i][j] = 'p';
				}
				if (i == SIZE - 2) { // White pawns
					board[i][j] = 'P';
				}
				if (i == SIZE - 1) {
					board[i][j] = white_valuable_piece[j];
				}
			}
		}
	}

	void print_board (char board[SIZE][SIZE]) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				std::cout << board[i][j] << " ";
			}
			std::cout << "\n";
		}
	}

	void add_piece (char board[SIZE][SIZE], char piece, int row, int column) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (i == row && j == column) {
					board[i][j] = piece;
				}
			}
		}
	}

	void move_pawn (char board[SIZE][SIZE], char piece) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				
			}
		}
	}
};

class Piece {
public:
	char piece;
	bool color;
	int row;
	int column;

	Piece (char piece_t, bool color_t, int row_t, int column_t) {
		piece = piece_t;
		color = color_t;
		row = row_t;
		column = column_t;
	};
	~Piece() {};

	char get_piece () {
		return piece;
	}

	void set_piece (char piece_t) {
		piece = piece_t;
	}

	bool get_color () {
		return color;
	}

	void set_color (bool color_t) {
		color = color_t;
	}

	int get_row () {
		return row;
	}

	void set_row (int row_t) {
		row = row_t;
	}

	int get_column () {
		return column;
	}

	void set_column (int column_t) {
		column = column_t;
	}
};

int main () {
	Minichess m;
	char board[SIZE][SIZE];
	Piece p('p', true, 4, 2);

	int tmp = p.get_column();
	std::cout << "La pièce est " << tmp << "\n";

	Piece t('p', false, 4, 2);
	t.set_piece('K');
	t.set_color(true);
	t.set_row(1);
	t.set_column(3);

	std::cout << t.get_piece() <<
	t.get_color() <<
	t.get_row() <<
	t.get_column() << "\n";

	m.create_board(board);
	//m.init_board(board);
	m.add_piece(board, 'P', 4, 2);
	m.print_board(board);

	std::cout << "\n";
	
	return 0;
}