#include "minichess.hpp"

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

void init_board (char board[SIZE][SIZE]) {
	char white_valuable_piece[SIZE] = {'R', 'N', 'B', 'Q', 'K'};
	char black_valuable_piece[SIZE] = {'r', 'n', 'b', 'q', 'k'};

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

void initialized_next_nullptr (std::unique_ptr<Node>& tree) {
	int i;
	for (i = 0; i < SIZE * SIZE; i++) {
		tree->_next.push_back(nullptr);
	}
}

void allocate_node (std::unique_ptr<Node>& tree, int number_move) {
	int i;
	for (i = 0; i < SIZE * SIZE; i++) {
		if (i == number_move) {
			tree->_next[i] = std::make_unique<Node> ();
		}
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

int is_uppercase (char piece) {
	if (piece >= 65 && piece <= 90) {
		return 1;
	} else if (piece >= 97 && piece <= 122) {
		return -1;	
	}
	return 0;
}

bool square_is_free (char board[SIZE][SIZE], int x, int y) {
	if (board[x][y] == '.')
		return true;
	return false;
}

void copy_tab (std::unique_ptr<Node>& node_child, std::unique_ptr<Node>& parent) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			node_child->_board[i][j] = parent->_board[i][j];
		}
	}
}

bool is_enemy (char board[SIZE][SIZE], int x, int y, bool turn) {
	if (turn == true) {
		if (is_uppercase(board[x][y]) == -1) {
			return 1;	
		} else {
			return 0;
		}
	} else 
	if (turn == false) {
		if (is_uppercase(board[x][y]) == 1) {
			return 1;
		} else {
			return 0;
		}
	}
	return 0;
}

int calculate_value_board (std::unique_ptr<Node>& tree) {
	int i, j;
	int score_evaluation = 0;
	std::map<char, int> piece_value {{'P', 1}, {'N', 3}, {'B', 3}, {'R', 5}, {'Q', 9}, {'K', 90},
								 {'p', -1}, {'n', -3}, {'b', -3}, {'r', -5}, {'q', -9}, {'k', -90}};

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (tree->_board[i][j] != '.') {
				for (std::map<char, int>::iterator it = piece_value.begin(); it != piece_value.end(); ++it) {
					if (tree->_board[i][j] == it->first) {
						score_evaluation += it->second;
					}
				}
			}
		}
	}
	return score_evaluation;
}

/**
 * The children nodes are allocate and initialized during the attack
 */

int move_piece (std::unique_ptr<Node>& tree, char piece, int x, int y, int& number_move, bool& turn) {
	char enemy_piece;

	if (square_is_free(tree->_board, x, y) == true) { // If the square in x, y is free
		tree->_board[x][y] = piece;
		allocate_node(tree, number_move);
		//print_board(tree->_board);
		tree->_value = calculate_value_board(tree);
		tree->_next[number_move]->_value = calculate_value_board(tree);
		
		copy_tab(tree->_next[number_move], tree);
		number_move++;
		tree->_board[x][y] = '.';
	} else {
		if (is_enemy(tree->_board, x, y, turn) == 1) { // If the square contains an enemy piece
			if (tree->_board[x][y] == 'k' || tree->_board[x][y] == 'K') // A piece can't "eat" a king
				return 1;
			enemy_piece = tree->_board[x][y];
			tree->_board[x][y] = piece;
			allocate_node(tree, number_move);
			//print_board(tree->_board);
			tree->_value = calculate_value_board(tree);
			tree->_next[number_move]->_value = calculate_value_board(tree);
			
			copy_tab(tree->_next[number_move], tree);
			number_move++;
			tree->_board[x][y] = enemy_piece;
			return 1;
		} else {
			return -1;
		}
	}
	return 0;
}

int bishop_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;

	x_initial_position = x;
	y_initial_position = y;

	while (x != 0 && y != SIZE - 1) { // Moves up/right
		x -= 1;
		y += 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'b' || tree->_board[x][y] == 'q')
					return 1;
				break;
			} else {
				if (tree->_board[x][y] == 'B' || tree->_board[x][y] == 'Q')
					return 1;
				break;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	while (x != SIZE - 1 && y != SIZE - 1) { // Moves right/down
		x += 1;
		y += 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'b' || tree->_board[x][y] == 'q')
					return 1;
				break;
			} else {
				if (tree->_board[x][y] == 'B' || tree->_board[x][y] == 'Q')
					return 1;
				break;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	while (x != SIZE - 1 && y != 0) { // Moves down/left
		x += 1;
		y -= 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'b' || tree->_board[x][y] == 'q')
					return 1;
				break;
			} else {
				if (tree->_board[x][y] == 'B' || tree->_board[x][y] == 'Q')
					return 1;
				break;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	while (x != 0 && y != 0) { // Moves left/up
		x -= 1;
		y -= 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'b' || tree->_board[x][y] == 'q')
					return 1;
				break;
			} else {
				if (tree->_board[x][y] == 'B' || tree->_board[x][y] == 'Q')
					return 1;
				break;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;
	return 0;
}

int moves_bishop (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;
	char piece = tree->_board[x][y];
	int res_move_piece = 0;

	x_initial_position = x;
	y_initial_position = y;

	while (x != 0 && y != SIZE - 1) { // Moves up/right
		tree->_board[x][y] = '.';
		x -= 1;
		y += 1;
		res_move_piece = move_piece(tree, piece, x, y, number_move, turn);
		if (res_move_piece == 1 || res_move_piece == -1)
			break;
	}

	res_move_piece = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (x != SIZE - 1 && y != SIZE - 1) { // Moves right/down
		tree->_board[x][y] = '.';
		x += 1;
		y += 1;
		res_move_piece = move_piece(tree, piece, x, y, number_move, turn);
		if (res_move_piece == 1 || res_move_piece == -1)
			break;
	}

	res_move_piece = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (x != SIZE - 1 && y != 0) { // Moves down/left
		tree->_board[x][y] = '.';
		x += 1;
		y -= 1;
		res_move_piece = move_piece(tree, piece, x, y, number_move, turn);
		if (res_move_piece == 1 || res_move_piece == -1)
			break;
	}

	res_move_piece = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (x != 0 && y != 0) { // Moves left/up
		tree->_board[x][y] = '.';
		x -= 1;
		y -= 1;
		res_move_piece = move_piece(tree, piece, x, y, number_move, turn);
		if (res_move_piece == 1 || res_move_piece == -1)
			break;
	}

	res_move_piece = 0;
	x = x_initial_position;
	y = y_initial_position;
	tree->_board[x][y] = piece;
	return 0;
}

int rook_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;

	x_initial_position = x;
	y_initial_position = y;

	while (x != 0) { // Moves up
		x -= 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'r' || tree->_board[x][y] == 'q')
					return 1;
				break;
			} else {
				if (tree->_board[x][y] == 'R' || tree->_board[x][y] == 'Q')
					return 1;
				break;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	while (y != SIZE - 1) { // Moves right
		y += 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'r' || tree->_board[x][y] == 'q')
					return 1;
				break;
			} else {
				if (tree->_board[x][y] == 'R' || tree->_board[x][y] == 'Q')
					return 1;
				break;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	while (x != SIZE - 1) { // Moves down
		x += 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'r' || tree->_board[x][y] == 'q')
					return 1;
				break;
			} else {
				if (tree->_board[x][y] == 'R' || tree->_board[x][y] == 'Q')
					return 1;
				break;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	while (y != 0) { // Moves left
		y -= 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'r' || tree->_board[x][y] == 'q')
					return 1;
				break;
			} else {
				if (tree->_board[x][y] == 'R' || tree->_board[x][y] == 'Q')
					return 1;
				break;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;
	return 0;
}

int moves_rook (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;
	char piece = tree->_board[x][y];
	int res_move_piece = 0;

	x_initial_position = x;
	y_initial_position = y;

	while (x != 0) { // Moves up
		tree->_board[x][y] = '.';
		x -= 1;
		// Create a child node and store the state of the board inside of it
		res_move_piece = move_piece(tree, piece, x, y, number_move, turn);
		if (res_move_piece == 1 || res_move_piece == -1)
			break;
	}

	res_move_piece = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (y != SIZE - 1) { // Moves right
		tree->_board[x][y] = '.';
		y += 1;
		res_move_piece = move_piece(tree, piece, x, y, number_move, turn);
		if (res_move_piece == 1 || res_move_piece == -1)
			break;
	}

	res_move_piece = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (x != SIZE - 1) { // Moves down
		tree->_board[x][y] = '.';
		x += 1;
		res_move_piece = move_piece(tree, piece, x, y, number_move, turn);
		if (res_move_piece == 1 || res_move_piece == -1)
			break;
	}

	res_move_piece = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (y != 0) { // Moves left
		tree->_board[x][y] = '.';
		y -= 1;
		res_move_piece = move_piece(tree, piece, x, y, number_move, turn);
		if (res_move_piece == 1 || res_move_piece == -1)
			break;
	}

	res_move_piece = 0;
	x = x_initial_position;
	y = y_initial_position;
	tree->_board[x][y] = piece;
	return 0;
}

void moves_queen (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) { // Queen acts like a rook and a bishop
	moves_rook(tree, x, y, number_move, turn);
	moves_bishop(tree, x, y, number_move, turn);
}

int knight_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;

	x_initial_position = x;
	y_initial_position = y;

	if (x > 1 && y < SIZE - 1) { // Moves 2*up/1*right
		x -= 2;
		y += 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'n')
					return 1;
			} else {
				if (tree->_board[x][y] == 'N')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != 0 && y < SIZE - 2) { // Moves 1*up/2*right
		x -= 1;
		y += 2;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'n')
					return 1;
			} else {
				if (tree->_board[x][y] == 'N')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1 && y < SIZE - 2) { // Moves 2*right/1*down
		x += 1;
		y += 2;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'n')
					return 1;
			} else {
				if (tree->_board[x][y] == 'N')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x < SIZE - 2 && y != SIZE - 1) { // Moves 1*right/2*down
		x += 2;
		y += 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'n')
					return 1;
			} else {
				if (tree->_board[x][y] == 'N')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x < SIZE - 2 && y != 0) { // Moves 2*down/1*left
		x += 2;
		y -= 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'n')
					return 1;
			} else {
				if (tree->_board[x][y] == 'N')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1 && y > 1) { // Moves 1*down/2*left
		x += 1;
		y -= 2;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'n')
					return 1;
			} else {
				if (tree->_board[x][y] == 'N')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != 0 && y > 1) { // Moves 2*left/1*up
		x -= 1;
		y -= 2;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'n')
					return 1;
			} else {
				if (tree->_board[x][y] == 'N')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x > 1 && y != 0) { // Moves 1*left/2*up
		x -= 2;
		y -= 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'n')
					return 1;
			} else {
				if (tree->_board[x][y] == 'N')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;
	return 0;
}

int moves_knight (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;
	char piece = tree->_board[x][y];

	x_initial_position = x;
	y_initial_position = y;

	if (x > 1 && y < SIZE - 1) { // Moves 2*up/1*right
		tree->_board[x][y] = '.';
		x -= 2;
		y += 1;
		move_piece(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != 0 && y < SIZE - 2) { // Moves 1*up/2*right
		tree->_board[x][y] = '.';
		x -= 1;
		y += 2;
		move_piece(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1 && y < SIZE - 2) { // Moves 2*right/1*down
		tree->_board[x][y] = '.';
		x += 1;
		y += 2;
		move_piece(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x < SIZE - 2 && y != SIZE - 1) { // Moves 1*right/2*down
		tree->_board[x][y] = '.';
		x += 2;
		y += 1;
		move_piece(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x < SIZE - 2 && y != 0) { // Moves 2*down/1*left
		tree->_board[x][y] = '.';
		x += 2;
		y -= 1;
		move_piece(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1 && y > 1) { // Moves 1*down/2*left
		tree->_board[x][y] = '.';
		x += 1;
		y -= 2;
		move_piece(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != 0 && y > 1) { // Moves 2*left/1*up
		tree->_board[x][y] = '.';
		x -= 1;
		y -= 2;
		move_piece(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x > 1 && y != 0) { // Moves 1*left/2*up
		tree->_board[x][y] = '.';
		x -= 2;
		y -= 1;
		move_piece(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;
	tree->_board[x][y] = piece;
	return 0;
}

int pawn_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;

	x_initial_position = x;
	y_initial_position = y;

	if (turn == true) { // Uppercase pawn moves
		if (x != 0) {
			if (y != SIZE - 1) {
				x -= 1;
				y += 1;
				if (square_is_free(tree->_board, x, y) == false) {
					if (tree->_board[x][y] == 'p')
						return 1;
				}
			}

			x = x_initial_position;
			y = y_initial_position;

			if (y != 0) {
				x -= 1;
				y -= 1;
				if (square_is_free(tree->_board, x, y) == false) {
					if (tree->_board[x][y] == 'p')
						return 1;
				}
			}
			
			x = x_initial_position;
			y = y_initial_position;	
		}
	} else {
		if (x != SIZE - 1) {
			if (y != SIZE - 1) {
				x += 1;
				y += 1;
				if (square_is_free(tree->_board, x, y) == false) {
					if (tree->_board[x][y] == 'P')
						return 1;
				}
			}

			x = x_initial_position;
			y = y_initial_position;

			if (y != 0) {
				x += 1;
				y -= 1;
				if (square_is_free(tree->_board, x, y) == false) {
					if (tree->_board[x][y] == 'P')
						return 1;
				}
			}
			
			x = x_initial_position;
			y = y_initial_position;	
		}
	}

	x = x_initial_position;
	y = y_initial_position;
	return 0;
}

int moves_pawn (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;
	char piece = tree->_board[x][y];

	x_initial_position = x;
	y_initial_position = y;

	if (turn == true && x != 0) { // Uppercase pawn moves
		tree->_board[x][y] = '.';
		if (is_enemy(tree->_board, x - 1, y + 1, turn) == 1 && tree->_board[x - 1][y - 1] != 'k' && y != SIZE - 1) { // Priority to attack up/right before to move
			move_piece(tree, piece, x - 1, y + 1, number_move, turn);
		}

		if (is_enemy(tree->_board, x - 1, y - 1, turn) == 1 && tree->_board[x - 1][y - 1] != 'k' && y != 0) { // Priority to attack up/left before to move
			move_piece(tree, piece, x - 1, y - 1, number_move, turn);
		}

		if (square_is_free(tree->_board, x - 1, y) == true) { // If in front of the pawn, the square is free
			x -= 1;
			move_piece(tree, piece, x, y, number_move, turn);
		}
	} else if (turn == false && x != SIZE - 1) { // Lowercase pawn moves
		tree->_board[x][y] = '.';
		if (is_enemy(tree->_board, x + 1, y + 1, turn) == 1 && tree->_board[x + 1][y + 1] != 'K' && y != SIZE - 1) { // Priority to attack down/right before to move
			move_piece(tree, piece, x + 1, y + 1, number_move, turn);
		}

		if (is_enemy(tree->_board, x + 1, y - 1, turn) == 1 && tree->_board[x + 1][y - 1] != 'K' && y != 0) { // Priority to attack down/left before to move
			move_piece(tree, piece, x + 1, y - 1, number_move, turn);
		}
		if (square_is_free(tree->_board, x + 1, y) == true) { // If in front of the pawn, the square is free
			x += 1;
			move_piece(tree, piece, x, y, number_move, turn);
		}
	}

	x = x_initial_position;
	y = y_initial_position;
	tree->_board[x][y] = piece;

	return 0;
}

int king_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;

	x_initial_position = x;
	y_initial_position = y;
	
	if (x != 0) { // Moves up
		x -= 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'k')
					return 1;
			} else {
				if (tree->_board[x][y] == 'K')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != 0 && y != SIZE - 1) { // Moves up/right
		x -= 1;
		y += 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'k')
					return 1;
			} else {
				if (tree->_board[x][y] == 'K')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (y != SIZE - 1) { // Moves right
		y += 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'k')
					return 1;
			} else {
				if (tree->_board[x][y] == 'K')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1 && y != SIZE - 1) { // Moves right/down
		x += 1;
		y += 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'k')
					return 1;
			} else {
				if (tree->_board[x][y] == 'K')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1) { // Moves down
		x += 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'k')
					return 1;
			} else {
				if (tree->_board[x][y] == 'K')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1 && y != 0) { // Moves down/left
		x += 1;
		y -= 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'k')
					return 1;
			} else {
				if (tree->_board[x][y] == 'K')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (y != 0) { // Moves left
		y -= 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'k')
					return 1;
			} else {
				if (tree->_board[x][y] == 'K')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != 0 && y != 0) { // Moves left/up
		x -= 1;
		y -= 1;
		if (square_is_free(tree->_board, x, y) == false) {
			if (turn == true) {
				if (tree->_board[x][y] == 'k')
					return 1;
			} else {
				if (tree->_board[x][y] == 'K')
					return 1;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;
	return 0;
}

int enemy_attacks_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	/*if (king_attacks_king(tree, x, y, number_move, turn) == 1) {
		return 1;
	}*/
	if (rook_attacks_king(tree, x, y, number_move, turn) == 1) {
		return 1;
	}
	if (bishop_attacks_king(tree, x, y, number_move, turn) == 1) {
		return 1;
	}
	if (knight_attacks_king(tree, x, y, number_move, turn) == 1) {
		return 1;
	}
	if (pawn_attacks_king(tree, x, y, number_move, turn) == 1) {
		return 1;
	}
	return 0;
}

int moves_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;
	int lose = 0;
	int max_adjacent_free_square = 8; // Theoritical number of available movement
	int adjacent_check_square = 0;    // Number of check after 1 movement of the king
	char piece = tree->_board[x][y];

	x_initial_position = x;
	y_initial_position = y;

	enemy_attacks_king(tree, x, y, number_move, turn);

	if (x != 0) { // Moves up
		tree->_board[x][y] = '.';
		x -= 1;
		// If there is no enemy king in an adjacent square
		if (king_attacks_king(tree, x, y, number_move, turn) == 0) { 
			move_piece(tree, piece, x, y, number_move, turn);
			adjacent_check_square += enemy_attacks_king(tree, x, y, number_move, turn);
		}
	} else {
		max_adjacent_free_square--;
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != 0 && y != SIZE - 1) { // Moves up/right
		tree->_board[x][y] = '.';
		x -= 1;
		y += 1;
		if (king_attacks_king(tree, x, y, number_move, turn) == 0) { 
			move_piece(tree, piece, x, y, number_move, turn);
			adjacent_check_square += enemy_attacks_king(tree, x, y, number_move, turn);
		}
	} else {
		max_adjacent_free_square--;
	}


	x = x_initial_position;
	y = y_initial_position;

	if (y != SIZE - 1) { // Moves right
		tree->_board[x][y] = '.';
		y += 1;
		if (king_attacks_king(tree, x, y, number_move, turn) == 0) { 
			move_piece(tree, piece, x, y, number_move, turn);
			adjacent_check_square += enemy_attacks_king(tree, x, y, number_move, turn);
		}
	} else {
		max_adjacent_free_square--;
	}


	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1 && y != SIZE - 1) { // Moves right/down
		tree->_board[x][y] = '.';
		x += 1;
		y += 1;
		if (king_attacks_king(tree, x, y, number_move, turn) == 0) { 
			move_piece(tree, piece, x, y, number_move, turn);
			adjacent_check_square += enemy_attacks_king(tree, x, y, number_move, turn);
		}
	} else {
		max_adjacent_free_square--;
	}


	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1) { // Moves down
		tree->_board[x][y] = '.';
		x += 1;
		if (king_attacks_king(tree, x, y, number_move, turn) == 0) { 
			move_piece(tree, piece, x, y, number_move, turn);
			adjacent_check_square += enemy_attacks_king(tree, x, y, number_move, turn);
		}
	} else {
		max_adjacent_free_square--;
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1 && y != 0) { // Moves down/left
		tree->_board[x][y] = '.';
		x += 1;
		y -= 1;
		if (king_attacks_king(tree, x, y, number_move, turn) == 0) { 
			move_piece(tree, piece, x, y, number_move, turn);
			adjacent_check_square += enemy_attacks_king(tree, x, y, number_move, turn);
		}
	} else {
		max_adjacent_free_square--;
	}

	x = x_initial_position;
	y = y_initial_position;

	if (y != 0) { // Moves left
		tree->_board[x][y] = '.';
		y -= 1;
		if (king_attacks_king(tree, x, y, number_move, turn) == 0) { 
			move_piece(tree, piece, x, y, number_move, turn);
			adjacent_check_square += enemy_attacks_king(tree, x, y, number_move, turn);
		}
	} else {
		max_adjacent_free_square--;
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != 0 && y != 0) { // Moves left/up
		tree->_board[x][y] = '.';
		x -= 1;
		y -= 1;
		if (king_attacks_king(tree, x, y, number_move, turn) == 0) { 
			move_piece(tree, piece, x, y, number_move, turn);
			adjacent_check_square += enemy_attacks_king(tree, x, y, number_move, turn);
		}
	} else {
		max_adjacent_free_square--;
	}

	x = x_initial_position;
	y = y_initial_position;
	tree->_board[x][y] = piece;

	if (max_adjacent_free_square == adjacent_check_square) {
		if (turn == true) {
			tree->_value -= INF;
			lose = 1;
		} else {
			tree->_value += INF;
			lose = 1;
		}
	}

	return lose;
}

int select_piece (std::unique_ptr<Node>& tree, int i, int j, int& number_move, bool& turn) {

	if (turn == true) {
		if (tree->_board[i][j] == 'P') {
			moves_pawn(tree, i, j, number_move, turn);
		}
		if (tree->_board[i][j] == 'R') {
			moves_rook(tree, i, j, number_move, turn);
		}
		if (tree->_board[i][j] == 'B') {
			moves_bishop(tree, i, j, number_move, turn);
		}
		if (tree->_board[i][j] == 'Q') {
			moves_queen(tree, i, j, number_move, turn);
		}
		if (tree->_board[i][j] == 'N') {
			moves_knight(tree, i, j, number_move, turn);
		}
		if (tree->_board[i][j] == 'K') {
			if (moves_king(tree, i, j, number_move, turn) == 1) {
				return 1;
			}
		}
		
	} else {
		if (tree->_board[i][j] == 'p') {
			moves_pawn(tree, i, j, number_move, turn);
		}
		if (tree->_board[i][j] == 'r') {
			moves_rook(tree, i, j, number_move, turn);
		}
		if (tree->_board[i][j] == 'b') {
			moves_bishop(tree, i, j, number_move, turn);
		}
		if (tree->_board[i][j] == 'q') {
			moves_queen(tree, i, j, number_move, turn);
		}
		if (tree->_board[i][j] == 'n') {
			moves_knight(tree, i, j, number_move, turn);
		}
		if (tree->_board[i][j] == 'k') {
			if (moves_king(tree, i, j, number_move, turn) == 1) {
				return 1;
			}
		}
		
	}
	return 0;
}

int min (int a, int b) {
	if (a < b)
		return a;
	return b;
}

int max (int a, int b) {
	if (a > b)
		return a;
	return b;
}

int checkmate (std::unique_ptr<Node>& tree, int& number_move, bool& turn) {
	int i, j;
	char king;
	if (turn == true) {
		king = 'K';
	} else {
		king = 'k';
	}
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (tree->_board[i][j] == king) {
				if (enemy_attacks_king(tree, i, j, number_move, turn) == 1) {
					return 1;
				}
			}
		}
	}
	return 0;
}

int alphabeta (std::unique_ptr<Node>& tree, int number_move, bool turn, int depth, int alpha, int beta) {
	int i, j, k;
	int res = 0;

	initialized_next_nullptr (tree);

	if (depth == 0) // Victory condition
		return tree->_value;

	if (turn == false) { // Lowercase - alpha
		res = INF;
		//if (checkmate(tree, number_move, turn) == 1)
		//	return tree->_value + INF;
		
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (tree->_board[i][j] != '.') {
					select_piece (tree, i, j, number_move, turn);
				}
			}
		}
		for (k = 0; k < number_move; k++) {
			res = min(res, alphabeta(tree->_next[k], 0, true, depth - 1, alpha, beta));
			if (alpha >= res) {
				return res;
			}
			beta = min(beta, res);
			return beta;
		}

	} else {  // Uppercase - beta
		res = -INF;
		//if (checkmate(tree, number_move, turn) == 1)
		//	return tree->_value - INF;

		for (i = SIZE - 1; i >= 0; i--) {
			for (j = 0; j < SIZE; j++) {
				if (tree->_board[i][j] != '.') {
					select_piece (tree, i, j, number_move, turn);
				}
			}
		}
		for (k = 0; k < number_move; k++) {
			res = max(res, alphabeta(tree->_next[k], 0, false, depth - 1, alpha, beta));
			if (res >= beta) {
				return res;
			}
			alpha = max(alpha, res);
		}
	}
	return res;
}

void print_node (std::unique_ptr<Node>& tree) {
	int i;
	if (tree) {
		std::cout << "Score : " << tree->_value << "\n";
		print_board(tree->_board);
		for (i = 0; i < SIZE * SIZE; i++) {
			if (tree->_next[i])
				print_node(tree->_next[i]);
		}
	}
}

void select_problem (std::unique_ptr<Node>& tree) {
	int n = 0;
	std::cout << "Choose a problem (write between 0 to 4): \n";
	std::cin >> n;
	switch (n) {
		case 0:
			init_board(tree->_board);
			break;
		case 1:
			add_piece(tree->_board, 'K', 3, 3);
			add_piece(tree->_board, 'R', 3, 0);
			add_piece(tree->_board, 'R', 4, 1);
			add_piece(tree->_board, 'k', 0, 3);
			break;
		case 2:
			add_piece(tree->_board, 'K', 3, 0);
			add_piece(tree->_board, 'Q', 4, 2);
			add_piece(tree->_board, 'R', 4, 1);
			add_piece(tree->_board, 'k', 0, 3);
			break;
		case 3:
			add_piece(tree->_board, 'K', 2, 3);
			add_piece(tree->_board, 'B', 4, 2);
			add_piece(tree->_board, 'B', 4, 1);
			add_piece(tree->_board, 'p', 1, 3);
			add_piece(tree->_board, 'k', 0, 3);
			break;
		case 4:
			add_piece(tree->_board, 'K', 2, 0);
			add_piece(tree->_board, 'N', 2, 4);
			add_piece(tree->_board, 'N', 1, 1);
			add_piece(tree->_board, 'b', 1, 3);
			add_piece(tree->_board, 'k', 0, 3);
			break;
		default :
			init_board(tree->_board);
			break;
	}

}

int main () {
	std::unique_ptr<Node> tree;
	tree = std::make_unique<Node> ();
	int depth = 2;

	bool turn = true;

	create_board(tree->_board);
	select_problem(tree);

	//init_board(tree->_board);

	//add_piece(tree->_board, 'k', 0, 2);
	//add_piece(tree->_board, 'K', 4, 2);

	print_board(tree->_board);

	int res = alphabeta(tree, 0, turn, depth, -INF, INF);
	//std::cout << "Résultat : " << res << "\n";
	
	//std::cout << "///////////////////////////////////////\nDEBUT DU PRINT NODE\n";

	/*if (tree) {
		tree->_value = calculate_value_board(tree);
		print_node(tree);
	} else {
		tree->_value = calculate_value_board(tree);
		print_board(tree->_board);
	}*/

	std::cout << "Résultat : " << res << "\n";

	return 0;
}