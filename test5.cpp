#include <iostream>
#include <vector>
#include <memory>
#include <map>
#define SIZE 5
#define INF 1;

/**
 * Run : g++ -O3 -std=c++14 -Wall test5.cpp
 */

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

/*std::unique_ptr<Node> allocate_next (std::unique_ptr<Node> tree) {
	int i;
	for (i = 0; i < SIZE * SIZE; i++) {
		tree->_next.push_back(std::make_unique<Node> ());
	}
	return std::move(tree);
}*/

void allocate_node (std::unique_ptr<Node>& tree, int number_move) {
	int i;
	for (i = 0; i < SIZE * SIZE; i++) {
		if (i == number_move)
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

bool is_ennemy (char board[SIZE][SIZE], int x, int y, bool turn) {
	if (turn == true) {
		if (is_uppercase(board[x][y]) == -1) {
			std::cout << "Le " << board[x][y] << " en " << x << ","<< y << " est attaqué\n";
			return 1;	
		} else {
			return 0;
		}
	} else 
	if (turn == false) {
		if (is_uppercase(board[x][y]) == 1) {
			std::cout << "Le " << board[x][y] << " en " << x << ","<< y << " est attaqué\n";
			return 1;
		} else {
			return 0;
		}
	}
	return 0;
}

//int checkmate (std:unique)

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
	std::cout << "SCORE EVALUATION : "<< score_evaluation << "\n";
	return score_evaluation;
}

/**
 * The children nodes are allocate during the attack
 */

int move_attack (std::unique_ptr<Node>& tree, char piece, int x, int y, int& number_move, bool& turn) {
	char ennemy_piece;

	if (square_is_free(tree->_board, x, y) == true) { // If the square in x, y is free
		std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
		tree->_board[x][y] = piece;
		allocate_node(tree, number_move);
		print_board(tree->_board);
		tree->_value = calculate_value_board(tree);
		tree->_next[number_move]->_value = calculate_value_board(tree);
		
		copy_tab(tree->_next[number_move], tree);
		number_move++;
		tree->_board[x][y] = '.';
	} else {
		if (is_ennemy(tree->_board, x, y, turn) == 1) { // If the square contains an ennemy piece
			ennemy_piece = tree->_board[x][y];
			tree->_board[x][y] = piece;
			allocate_node(tree, number_move);
			print_board(tree->_board);
			tree->_value = calculate_value_board(tree);
			tree->_next[number_move]->_value = calculate_value_board(tree);
			
			copy_tab(tree->_next[number_move], tree);
			number_move++;
			tree->_board[x][y] = ennemy_piece;
			return 1;
		} else {
			return -1;
		}
	}
	return 0;
}

int moves_bishop (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;
	char piece = tree->_board[x][y];
	int res_move_attack = 0;

	x_initial_position = x;
	y_initial_position = y;

	while (x != 0 && y != SIZE - 1) { // Moves up/right
		tree->_board[x][y] = '.';
		x -= 1;
		y += 1;
		res_move_attack = move_attack(tree, piece, x, y, number_move, turn);
		if (res_move_attack == 1 || res_move_attack == -1)
			break;
	}

	res_move_attack = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (x != SIZE - 1 && y != SIZE - 1) { // Moves right/down
		tree->_board[x][y] = '.';
		x += 1;
		y += 1;
		std::cout << tree->_board[x][y] << " en x : " << x << ", y : " << y << "\n";
		res_move_attack = move_attack(tree, piece, x, y, number_move, turn);
		if (res_move_attack == 1 || res_move_attack == -1)
			break;
	}

	res_move_attack = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (x != SIZE - 1 && y != 0) { // Moves down/left
		tree->_board[x][y] = '.';
		x += 1;
		y -= 1;
		res_move_attack = move_attack(tree, piece, x, y, number_move, turn);
		if (res_move_attack == 1 || res_move_attack == -1)
			break;
	}

	res_move_attack = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (x != 0 && y != 0) { // Moves left/up
		tree->_board[x][y] = '.';
		x -= 1;
		y -= 1;
		res_move_attack = move_attack(tree, piece, x, y, number_move, turn);
		if (res_move_attack == 1 || res_move_attack == -1)
			break;
	}

	res_move_attack = 0;
	x = x_initial_position;
	y = y_initial_position;
	tree->_board[x][y] = piece;
	return 0;
}

int moves_rook (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;
	char piece = tree->_board[x][y];
	int res_move_attack = 0;

	x_initial_position = x;
	y_initial_position = y;

	while (x != 0) { // Moves up
		tree->_board[x][y] = '.';
		x -= 1;
		res_move_attack = move_attack(tree, piece, x, y, number_move, turn);
		if (res_move_attack == 1 || res_move_attack == -1)
			break;
	}

	res_move_attack = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (y != SIZE - 1) { // Moves right
		tree->_board[x][y] = '.';
		y += 1;
		res_move_attack = move_attack(tree, piece, x, y, number_move, turn);
		if (res_move_attack == 1 || res_move_attack == -1)
			break;
	}

	res_move_attack = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (x != SIZE - 1) { // Moves down
		tree->_board[x][y] = '.';
		x += 1;
		res_move_attack = move_attack(tree, piece, x, y, number_move, turn);
		if (res_move_attack == 1 || res_move_attack == -1)
			break;
	}

	res_move_attack = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (y != 0) { // Moves left
		tree->_board[x][y] = '.';
		y -= 1;
		res_move_attack = move_attack(tree, piece, x, y, number_move, turn);
		if (res_move_attack == 1 || res_move_attack == -1)
			break;
	}

	res_move_attack = 0;
	x = x_initial_position;
	y = y_initial_position;
	tree->_board[x][y] = piece;
	return 0;
}

void moves_queen (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) { // Queen acts like a rook and a bishop
	moves_rook(tree, x, y, number_move, turn);
	moves_bishop(tree, x, y, number_move, turn);
}

int moves_knight (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;
	char piece = tree->_board[x][y];

	x_initial_position = x;
	y_initial_position = y;
	std::cout << "ICI en x : " << x << ", y : " << y << "\n";
	std::cout << "ICI en x_initial_position : " << x_initial_position << ", y_initial_position : " << y_initial_position << "\n";

	std::cout << "A\n";
	if (x > 1 && y < SIZE - 1) { // Moves 2*up/1*right
		tree->_board[x][y] = '.';
		x -= 2;
		y += 1;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;
	std::cout << "B\n";
	std::cout << tree->_board[x][y] << " en x : " << x << ", y : " << y << "\n";

	if (x != 0 && y < SIZE - 2) { // Moves 1*up/2*right
		tree->_board[x][y] = '.';
		x -= 1;
		y += 2;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1 && y < SIZE - 2) { // Moves 2*right/1*down
		tree->_board[x][y] = '.';
		x += 1;
		y += 2;
		std::cout << tree->_board[x][y] << " en x : " << x << ", y : " << y << "\n";
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x < SIZE - 2 && y != SIZE - 1) { // Moves 1*right/2*down
		tree->_board[x][y] = '.';
		x += 2;
		y += 1;
		std::cout << tree->_board[x][y] << " en x : " << x << ", y : " << y << "\n";
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	std::cout << "C\n";
	if (x < SIZE - 2 && y != 0) { // Moves 2*down/1*left
		tree->_board[x][y] = '.';
		x += 2;
		y -= 1;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x != SIZE - 1 && y > 1) { // Moves 1*down/2*left
		tree->_board[x][y] = '.';
		x += 1;
		y -= 2;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	std::cout << "D\n";
	if (x != 0 && y > 1) { // Moves 2*left/1*up
		tree->_board[x][y] = '.';
		x -= 1;
		y -= 2;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	if (x > 1 && y != 0) { // Moves 1*left/2*up
		tree->_board[x][y] = '.';
		x -= 2;
		y -= 1;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;
	tree->_board[x][y] = piece;
	return 0;
}

int moves_pawn (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;
	char piece = tree->_board[x][y];

	x_initial_position = x;
	y_initial_position = y;

	if (turn == true && x != 0) { // Uppercase pawn moves
		tree->_board[x][y] = '.';
		if (is_ennemy(tree->_board, x - 1, y + 1, turn) == 1 && y != SIZE - 1) { // Priority to attack up/right before to move
			move_attack(tree, piece, x - 1, y + 1, number_move, turn);
		}

		if (is_ennemy(tree->_board, x - 1, y - 1, turn) == 1 && y != 0) { // Priority to attack up/left before to move
			move_attack(tree, piece, x - 1, y - 1, number_move, turn);
		}

		if (square_is_free(tree->_board, x - 1, y) == true) { // If in front of the pawn, the square is free
			x -= 1;
			move_attack(tree, piece, x, y, number_move, turn);
		}
	} else if (turn == false && x != SIZE - 1) { // Lowercase pawn moves
		tree->_board[x][y] = '.';
		if (is_ennemy(tree->_board, x + 1, y + 1, turn) == 1 && y != SIZE - 1) { // Priority to attack down/right before to move
			move_attack(tree, piece, x + 1, y + 1, number_move, turn);
		}

		if (is_ennemy(tree->_board, x + 1, y - 1, turn) == 1 && y != 0) { // Priority to attack down/left before to move
			move_attack(tree, piece, x + 1, y - 1, number_move, turn);
		}
		if (square_is_free(tree->_board, x + 1, y) == true) { // If in front of the pawn, the square is free
			x += 1;
			move_attack(tree, piece, x, y, number_move, turn);
		}
	}

	x = x_initial_position;
	y = y_initial_position;
	tree->_board[x][y] = piece;

	return 0;
}

int moves_king (std::unique_ptr<Node>& tree, int x, int y, int& number_move, bool turn) {
	int x_initial_position, y_initial_position;
	char piece = tree->_board[x][y];

	x_initial_position = x;
	y_initial_position = y;
	std::cout << "ICI en x : " << x << ", y : " << y << "\n";
	std::cout << "ICI en x_initial_position : " << x_initial_position << ", y_initial_position : " << y_initial_position << "\n";

	std::cout << "King haut\n";
	if (x != 0) { // Moves up
		tree->_board[x][y] = '.';
		x -= 1;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;
	std::cout << "King haut/droite\n";
	std::cout << tree->_board[x][y] << " en x : " << x << ", y : " << y << "\n";

	if (x != 0 && y != SIZE - 1) { // Moves up/right
		tree->_board[x][y] = '.';
		x -= 1;
		y += 1;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;
	std::cout << "King droite\n";

	if (y != SIZE - 1) { // Moves right
		tree->_board[x][y] = '.';
		y += 1;
		std::cout << tree->_board[x][y] << " en x : " << x << ", y : " << y << "\n";
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	std::cout << "King bas/droite\n";

	if (x != SIZE - 1 && y != SIZE - 1) { // Moves right/down
		tree->_board[x][y] = '.';
		x += 1;
		y += 1;
		std::cout << tree->_board[x][y] << " en x : " << x << ", y : " << y << "\n";
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	std::cout << "King bas\n";
	if (x != SIZE - 1) { // Moves down
		tree->_board[x][y] = '.';
		x += 1;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	std::cout << "King bas/gauche\n";
	if (x != SIZE - 1 && y != 0) { // Moves down/left
		tree->_board[x][y] = '.';
		x += 1;
		y -= 1;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	std::cout << "King gauche\n";
	if (y != 0) { // Moves left
		tree->_board[x][y] = '.';
		y -= 1;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;

	std::cout << "King haut/gauche\n";
	if (x != 0 && y != 0) { // Moves left/up
		tree->_board[x][y] = '.';
		x -= 1;
		y -= 1;
		move_attack(tree, piece, x, y, number_move, turn);
	}

	x = x_initial_position;
	y = y_initial_position;
	tree->_board[x][y] = piece;
	return 0;
}

void select_piece (std::unique_ptr<Node>& tree, bool& turn) {
	int i, j;
	int number_move = 0;

	if (turn == true) {
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (tree->_board[i][j] == 'P') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_pawn(tree, i, j, number_move, turn);
				}
				if (tree->_board[i][j] == 'R') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_rook(tree, i, j, number_move, turn);
				}
				if (tree->_board[i][j] == 'B') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_bishop(tree, i, j, number_move, turn);
				}
				if (tree->_board[i][j] == 'Q') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_queen(tree, i, j, number_move, turn);
				}
				if (tree->_board[i][j] == 'N') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_knight(tree, i, j, number_move, turn);
				}
				if (tree->_board[i][j] == 'K') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_king(tree, i, j, number_move, turn);
				}
			}
		}
		turn = false;
	} else {
		for (i = SIZE - 1; i >= 0; i--) {
			for (j = 0; j < SIZE; j++) {
				if (tree->_board[i][j] == 'p') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_pawn(tree, i, j, number_move, turn);
				}
				if (tree->_board[i][j] == 'r') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_rook(tree, i, j, number_move, turn);
				}
				if (tree->_board[i][j] == 'b') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_bishop(tree, i, j, number_move, turn);
				}
				if (tree->_board[i][j] == 'q') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_queen(tree, i, j, number_move, turn);
				}
				if (tree->_board[i][j] == 'n') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_knight(tree, i, j, number_move, turn);
				}
				if (tree->_board[i][j] == 'k') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_king(tree, i, j, number_move, turn);
				}
			}
		}
		turn = true;
	}
}

/*int alphabeta (int tab[L][C], int prof, int joueur, int alpha, int beta) {
	int i;
	int res = 0;
	std::cout << "prof = " << prof <<"\n";

	if (prof == 0) {
		res = het(tab);
		return res;
	}

	if (joueur < 0) { // Tour de min et fait jouer max
		res = 11111;
		for (i = 0; i < C; i++) { // Pour chaque coup possible
			play(tab, i, 2);
			std::cout << "Joueur MIN joue :\n";
			std::cout << "joueur = "<<joueur<<"\n";
			std::cout << "coup joué = "<<i<< " prof = " << prof <<"\n";
			std::cout << "print jouer :\n";
			print_tab(tab);

			res = min(res, alphabeta(tab, prof - 1, abs(joueur), alpha, beta)); // res aura la valeur d'un noeud fils
			undo (tab, i);
			std::cout << "print annuler :\n";
			print_tab(tab);


			if (alpha >= res) {  // Si alpha (valeur du noeud père) est plus petit que son fils
				return alpha;    // Coupe alpha
			}
			beta = max(res, beta);
		}

	} else {          // Tour de max et fait jouer min
		res = -11111;
		for (i = 0; i < C; i++) {
			play(tab, i, 1);
			std::cout << "Joueur MAX joue :\n";
			std::cout << "joueur = "<<joueur<<"\n";
			std::cout << "coup joué = "<<i<< " prof = " << prof <<"\n";
			std::cout << "print jouer :\n";

			print_tab(tab);

			res = max(res, alphabeta(tab, prof - 1, -joueur, alpha, beta));
			std::cout << "print annuler :\n";
			undo (tab, i);

			if (res <= beta) {
				return beta;     // Coupe beta
			}
			alpha = min(alpha, res);	
		}
	}

	return res;
}*/

void playout (std::unique_ptr<Node>& tree, bool& turn) {
	int i = 0;
	while (i < 5) {
		select_piece (tree, turn);
		i++;
	}
}

/** PROBLEME AU NIVEAU de L'AFFICHAGE
 * POINTEUR ALLOUE MAIS VIDE
*/

void print_node (std::unique_ptr<Node>& tree) {
	int i;
	std::cout << tree.get() << "\n";
	std::cout << tree->_next.size() << "\n";
	std::cout << "Score : " << tree->_value << "\n";
	if (tree) {
		std::cout << "ICI\n";
		print_board(tree->_board);
		for (i = 0; i < static_cast<int>(tree->_next.size()); i++)
			print_node(tree->_next[i]);
	} else {
		std::cout << "NULL \n";
	}
}

int main () {
	std::unique_ptr<Node> tree = std::make_unique<Node> ();
	//tree->_next.push_back(std::make_unique<Node> ());
	//tree->_next[0] = nullptr;

	//std::unique_ptr<Node> tree;
	//allocate_node(tree);

	bool turn = true;

	create_board(tree->_board);

	init_board(tree->_board);

	//add_piece(tree->_board, 'P', 4, 0);
	//add_piece(tree->_board, 'p', 4, 4);
	//add_piece(tree->_board, 'P', 3, 1);
	
	//add_piece(tree->_board, 'P', 2, 2);
	add_piece(tree->_board, '.', 3, 2);

	print_board(tree->_board);

	/** On utilise std::move pour "déplacer" l'objet et non envoyer une copie de l'objet
	 *  car sinon, les allocations dans tree->next_ seront détruites 
	 *  à la fin de la fonction allocate_next()
	 */
	//tree = allocate_next(std::move(tree));
	/** 
	 *  Ou alors par référence, (ajout de & dans les arguments de allocate_next())
	 *  Une référence est un alias, c'est à dire, un autre nom/un pseudo dans l'autre fonction
	 *  Ce n'est ni une copie, ni un pointeur mais la variable elle-même
	 */
	//allocate_next(tree);

	std::cout << "DEBUT DE LA SELECTION\n";
	tree->_value = calculate_value_board(tree);
	select_piece(tree, turn);

	std::cout << "///////////////////////////////////////\nDEBUT DU PRINT NODE\n";

	if (tree) {
		tree->_value = calculate_value_board(tree);
		print_node(tree);
	} else {
		tree->_value = calculate_value_board(tree);
		print_board(tree->_board);
	}

	/*std::cout << tree->_next.size() << "\n";
	create_board(tree->_next[0]->_board);
	print_board(tree->_next[0]->_board);
*/
	//print_node(tree);

	return 0;
}