#include <iostream>
#include <vector>
#include <memory>
#define SIZE 3
#define INF 1;

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

bool is_uppercase (char piece) {
	if (piece >= 65 && piece <= 90)
		return true;
	return false;
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
		if (is_uppercase(board[x][y]) == false) {
			std::cout << "Le " << board[x][y] << " en " << x << ","<< y << " est attaqué\n";
			return 1;	
		} else {
			return 0;
		}
	} else 
	if (turn == false) {
		if (is_uppercase(board[x][y]) == true) {
			std::cout << "Le " << board[x][y] << " en " << x << ","<< y << " est attaqué\n";
			return 1;
		} else {
			return 0;
		}
	}
	return 0;
}

/**
 * FAUT RETOURNER LA VALEUR NUMBER_MOVE VERS MOVE_ROOK
 */

int move_attack (std::unique_ptr<Node>& tree, char piece, int x, int y, int number_move, bool turn) {
	if (square_is_free(tree->_board, x, y) == true) {
		std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
		tree->_board[x][y] = piece;
		allocate_node(tree, number_move);
		print_board(tree->_board);
		
		copy_tab(tree->_next[number_move], tree);
		number_move++;
		tree->_board[x][y] = '.';
	} else {
		if (is_ennemy(tree->_board, x, y, turn) == 1) {
			tree->_board[x][y] = piece;
			allocate_node(tree, number_move);
			print_board(tree->_board);
			
			copy_tab(tree->_next[number_move], tree);
			number_move++;
			tree->_board[x][y] = '.';
			return 1;
		}
	}
	return 0;
}

int moves_rook (std::unique_ptr<Node>& tree, int x, int y, bool turn) {
	int x_initial_position, y_initial_position;
	char piece = tree->_board[x][y];
	int number_move = 0;
	int res_move_attack = 0;

	x_initial_position = x;
	y_initial_position = y;

	while (x != 0) { // Moves up
		tree->_board[x][y] = '.';
		x -= 1;
		res_move_attack = move_attack(tree, piece, x, y, number_move, turn);
		if (res_move_attack == 1)
			break;
		/*if (square_is_free(tree->_board, x, y) == true) {
			std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
			tree->_board[x][y] = piece;
			allocate_node(tree, number_move);
			print_board(tree->_board);
			
			copy_tab(tree->_next[number_move], tree);
			number_move++;
			tree->_board[x][y] = '.';

		} else {
			if (is_ennemy(tree->_board, x, y, turn) == 1) {
				tree->_board[x][y] = piece;
				allocate_node(tree, number_move);
				print_board(tree->_board);
				
				copy_tab(tree->_next[number_move], tree);
				number_move++;
				tree->_board[x][y] = '.';
				break;
			}
		}*/
	}
	res_move_attack = 0;
	x = x_initial_position;
	y = y_initial_position;

	while (y != SIZE - 1) { // Moves right
		tree->_board[x][y] = '.';
		y += 1;
		res_move_attack = move_attack(tree, piece, x, y, number_move, turn);
		if (res_move_attack == 1)
			break;
		/*if (square_is_free(tree->_board, x, y) == true) {
			std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
			tree->_board[x][y] = piece;
			allocate_node(tree, number_move);
			print_board(tree->_board);
			
			copy_tab(tree->_next[number_move], tree);
			number_move++;
			tree->_board[x][y] = '.';

		} else {
			if (is_ennemy(tree->_board, x, y, turn) == 1) {
				tree->_board[x][y] = piece;
				allocate_node(tree, number_move);
				print_board(tree->_board);
				
				copy_tab(tree->_next[number_move], tree);
				number_move++;
				tree->_board[x][y] = '.';
				break;
			}
		}*/
	}

	x = x_initial_position;
	y = y_initial_position;

	while (x != SIZE - 1) { // Moves down
		tree->_board[x][y] = '.';
		x += 1;
		if (square_is_free(tree->_board, x, y) == true) {
			std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
			tree->_board[x][y] = piece;
			allocate_node(tree, number_move);
			print_board(tree->_board);
			
			copy_tab(tree->_next[number_move], tree);
			number_move++;
			tree->_board[x][y] = '.';

		} else {
			if (is_ennemy(tree->_board, x, y, turn) == 1) {
				tree->_board[x][y] = piece;
				allocate_node(tree, number_move);
				print_board(tree->_board);
				
				copy_tab(tree->_next[number_move], tree);
				number_move++;
				tree->_board[x][y] = '.';
				break;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;

	while (y != 0) { // Moves left
		tree->_board[x][y] = '.';
		y -= 1;
		if (square_is_free(tree->_board, x, y) == true) {
			std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
			tree->_board[x][y] = piece;
			allocate_node(tree, number_move);
			print_board(tree->_board);
			
			copy_tab(tree->_next[number_move], tree);
			number_move++;
			tree->_board[x][y] = '.';

		} else {
			if (is_ennemy(tree->_board, x, y, turn) == 1) {
				tree->_board[x][y] = piece;
				allocate_node(tree, number_move);
				print_board(tree->_board);
				
				copy_tab(tree->_next[number_move], tree);
				number_move++;
				tree->_board[x][y] = '.';
				break;
			}
		}
	}

	x = x_initial_position;
	y = y_initial_position;
	tree->_board[x][y] = piece;
	return 0;
}

void select_piece (std::unique_ptr<Node>& tree, bool turn) {
	int i, j;

	if (turn == true) {
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				/*if (board[i][j] == 'P') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_pawn(i, j);
				}*/
				if (tree->_board[i][j] == 'R') {
					std::cout << tree->_board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_rook(tree, i, j, turn);
				}
				/*if (board[i][j] == 'B') {
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
				}*/
			}
		}
		turn = false;
	}/* else {
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
	}*/
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


void print_node (std::unique_ptr<Node>& tree) {
	int i;
	std::cout << tree.get() << "\n";
	if (tree) {
		std::cout << "ICI\n";
		print_board(tree->_board);
		for (i = 0; i < SIZE * SIZE; i++)
			print_node(tree->_next[i]);
	} else {
		std::cout << "NULL \n";
	}
}

int main () {
	std::unique_ptr<Node> tree = std::make_unique<Node> ();
	//std::unique_ptr<Node> tree;
	//allocate_node(tree);
	bool turn = true;

	create_board(tree->_board);
	print_board(tree->_board);
	//init_board(tree->_board);

	add_piece(tree->_board, 'R', 1, 1);
	//add_piece(tree->_board, 'p', 0, 1);
	
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

	std::cout << "ICI\n";
	select_piece(tree, turn);

	std::cout << "TEST\n";
	print_board(tree->_next[0]->_board);

	/*std::cout << tree->_next.size() << "\n";
	create_board(tree->_next[0]->_board);
	print_board(tree->_next[0]->_board);
*/
	//print_node(tree);

	return 0;
}