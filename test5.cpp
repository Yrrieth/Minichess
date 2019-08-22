#include <iostream>
#include <vector>
#include <memory>
#define SIZE 3

class Node {
public:
	int _value;
	char _board[SIZE][SIZE];
	std::vector<std::unique_ptr<Node>> _next;

	Node () {
		std::cout << "Allocation\n";
	};
	~Node () {std::cout << "Désallocation\n";};
};

void create_board (char board[SIZE][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			board[i][j] = '.';
		}
	}
}

void print_board (char board[SIZE][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

/*void init_board (char board[SIZE][SIZE]) {
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
}*/

/*std::unique_ptr<Node> allocate_next (std::unique_ptr<Node> tree) {
	int i;
	for (i = 0; i < SIZE * SIZE; i++) {
		tree->_next.push_back(std::make_unique<Node> ());
	}
	return std::move(tree);
}*/

void allocate_next (std::unique_ptr<Node>& tree) {
	int i;
	for (i = 0; i < SIZE * SIZE; i++) {
		tree->_next.push_back(std::make_unique<Node> ());
	}
}

void add_piece (char board[SIZE][SIZE], char piece, int row, int column) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (i == row && j == column)
				board[i][j] = piece;
		}
	}
}

/*
void select_piece (char board) {
	int i, j;
	int score_evaluation = 0;
	int old_score_evaluation = 0;

	if (turn == true) {
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (board[i][j] == 'P') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_pawn(i, j);
				}
				if (board[i][j] == 'R') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_rook(i, j);
				}
				if (board[i][j] == 'B') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_bishop(i, j);
				}
				if (board[i][j] == 'Q') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_queen(i, j);
				}
				if (board[i][j] == 'N') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_knight(i, j);
				}
				if (board[i][j] == 'K') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_king(i, j);
				}
			}
		}
		turn = false;
	} else {
		for (i = SIZE - 1; i >= 0; i--) {
			for (j = 0; j < SIZE; j++) {
				if (board[i][j] == 'p') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_pawn(i, j);
				}
				if (board[i][j] == 'r') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_rook(i, j);
				}
				if (board[i][j] == 'b') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_bishop(i, j);
				}
				if (board[i][j] == 'q') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_queen(i, j);
				}
				if (board[i][j] == 'n') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_knight(i, j);
				}
				if (board[i][j] == 'k') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_king(i, j);
				}
			}
		}
		turn = true;
	}
}*/

/*
void print_node (Node tree) {
	if (tree._right != nullptr) {
		print_board(tree._board);
		print_node(tree._right);
	} else {
		std::cout << "NULL \n";
	}
}
*/
int main () {
	std::unique_ptr<Node> tree = std::make_unique<Node> ();

	create_board(tree->_board);
	print_board(tree->_board);
	//init_board(tree->_board);

	add_piece(tree->_board, 'p', 1, 2);
	
	print_board(tree->_board);

	/** On utilise std::move pour "déplacer" et non envoyer une copie de l'objet
	 *  car sinon, les allocations dans tree->next_ seront détruites 
	 *  à la fin de la fonction allocate_next()
	 */
	//tree = allocate_next(std::move(tree));
	/** 
	 *  Ou alors par référence, (ajout de & dans les arguments de allocate_next())
	 *  Une référence est un alias, c'est à dire, un autre nom/un pseudo dans l'autre fonction
	 *  Ce n'est ni une copie, ni un pointeur mais la variable elle-même
	 */
	allocate_next(tree);

	std::cout << "ICI\n";

	std::cout << tree->_next.size() << "\n";
	create_board(tree->_next[0]->_board);
	print_board(tree->_next[0]->_board);

	return 0;
}