#include <iostream>
#include <array>
#define SIZE 5

using namespace std;

class minichess {
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
};

int main () {
	minichess m;
	char board[SIZE][SIZE];

	m.create_board(board);
	m.init_board(board);
	m.print_board(board);

	std::cout << "\n";
	
	return 0;
}