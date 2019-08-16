#include "minichess.hpp"

void Minichess::create_board () {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			_board[i][j] = '.';
		}
	}
}

void Minichess::init_board () {
	char white_valuable_piece[SIZE] = {'R', 'B', 'N', 'Q', 'K'};
	char black_valuable_piece[SIZE] = {'r', 'b', 'n', 'q', 'k'};

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (i == 0) {
				_board[i][j] = black_valuable_piece[j];
			}
			if (i == 1) { // Black pawns
				_board[i][j] = 'p';
			}
			if (i == SIZE - 2) { // White pawns
				_board[i][j] = 'P';
			}
			if (i == SIZE - 1) {
				_board[i][j] = white_valuable_piece[j];
			}
		}
	}
}

void Minichess::print_board () {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			std::cout << _board[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void Minichess::add_piece (char piece, int row, int column) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (i == row && j == column) {
				_board[i][j] = piece;
			}
		}
	}
}

bool Minichess::is_ennemy (char piece, int x, int y) {
	if (square_is_free(x, y) == false) {
		if (_turn == true) {
			if (is_uppercase(_board[x][y]) == false) {
				std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
				_board[x][y] = piece;
				return 1;	
			} else {
				return 0;
			}
		} 
		if (_turn == false) {
			if (is_uppercase(_board[x][y]) == true) {
				std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
				_board[x][y] = piece;
				return 1;
			} else {
				return 0;
			}
		}
	}
	return 0;
}

int Minichess::bishop_attacks (int x, int y) {
	int x_initial_position, y_initial_position;
	char piece = _board[x][y];

		x_initial_position = x;
		y_initial_position = y;
		while (x != 0 && y != SIZE - 1) { // Up/right
			_board[x][y] = '.';
			x -= 1;
			y += 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					} else {
						break;
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					} else {
						break;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		while (x != SIZE - 1 && y != SIZE - 1) { // right/down
			_board[x][y] = '.';
			x += 1;
			y += 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					} else {
						break;
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					} else {
						break;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		while (x != SIZE - 1 && y != 0) { // down/left
			_board[x][y] = '.';
			x += 1;
			y -= 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					} else {
						break;
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					} else {
						break;
					}
				} 
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		while (x != 0 && y != 0) { // left/up
			_board[x][y] = '.';
			x -= 1;
			y -= 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					} else {
						break;
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					} else {
						break;
					}
				}
			}
		}
		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

	return 0;
}

void Minichess::moves_bishop (int x, int y) {
	int x_initial_position, y_initial_position;
	char piece = _board[x][y];

	x_initial_position = x;
	y_initial_position = y;
	std::cout << "ICI en x : " << x << ", y : " << y << "\n";
	std::cout << "ICI en x_initial_position : " << x_initial_position << ", y_initial_position : " << y_initial_position << "\n";

	if (bishop_attacks(x, y) == 0) { // If rook can't attack
		std::cout << "A\n";
		while (x != 0 && y != SIZE - 1) { // Moves up/right
			_board[x][y] = '.';
			x -= 1;
			y += 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				bishop_attacks(x, y);

				_board[x][y] = '.';
			}
		}
				std::cout << _board[x][y] << " en x : " << x << ", y : " << y << "\n";

		x = x_initial_position;
		y = y_initial_position;
		std::cout << "B\n";
				std::cout << _board[x][y] << " en x : " << x << ", y : " << y << "\n";


		while (x != SIZE - 1 && y != SIZE - 1) { // Moves right/down
			_board[x][y] = '.';
			x += 1;
			y += 1;
			std::cout << _board[x][y] << " en x : " << x << ", y : " << y << "\n";
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				bishop_attacks(x, y);

				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		std::cout << "C\n";
		while (x != SIZE - 1 && y != 0) { // Moves down/left
			_board[x][y] = '.';
			x += 1;
			y -= 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				bishop_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		std::cout << "D\n";
		while (x != 0 && y != 0) { // Moves left/up
			_board[x][y] = '.';
			x -= 1;
			y -= 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				bishop_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;
	}
}

int Minichess::rook_attacks (int x, int y) {
	int x_initial_position, y_initial_position;
	char piece = _board[x][y];

		x_initial_position = x;
		y_initial_position = y;
		while (x != 0) { // Up
			_board[x][y] = '.';
			x -= 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					} else {
						break;
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					} else {
						break;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		while (y != SIZE - 1) { // right
			_board[x][y] = '.';
			y += 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					} else {
						break;
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					} else {
						break;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		while (x != SIZE - 1) { // down
			_board[x][y] = '.';
			x += 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					} else {
						break;
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					} else {
						break;
					}
				} 
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		while (y != 0) { // left
			_board[x][y] = '.';
			y -= 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					} else {
						break;
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					} else {
						break;
					}
				}
			}
		}
		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

	return 0;
}

void Minichess::moves_rook (int x, int y) {
	int x_initial_position, y_initial_position;
	char piece = _board[x][y];

	x_initial_position = x;
	y_initial_position = y;

	if (rook_attacks(x, y) == 0) { // If rook can't attack

		while (x != 0) { // Moves up
			_board[x][y] = '.';
			x -= 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				rook_attacks(x, y);

				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		while (y != SIZE - 1) { // Moves right
			_board[x][y] = '.';
			y += 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				rook_attacks(x, y);

				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		while (x != SIZE - 1) { // Moves down
			_board[x][y] = '.';
			x += 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				rook_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		while (y != 0) { // Moves left
			_board[x][y] = '.';
			y -= 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				rook_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;
	}
}

void Minichess::moves_queen (int x, int y) {
	moves_rook(x, y);
	moves_bishop(x, y);
}

int Minichess::pawn_attacks (int x, int y) {
	int x_initial_position, y_initial_position;
	char piece = _board[x][y];

	if (_turn == true) {
		x_initial_position = x;
		y_initial_position = y;
		if (x != 0 && y != SIZE - 1) { // Up/right
			_board[x][y] = '.';
			x -= 1;
			y += 1;
			if (square_is_free(x, y) == false) {
				if (is_uppercase(_board[x][y]) == false) {
					std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
					_board[x][y] = piece;
					return 1;
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x != 0 && y != 0) { // Up/left
			_board[x][y] = '.';
			x -= 1;
			y -= 1;
			if (square_is_free(x, y) == false) {
				if (is_uppercase(_board[x][y]) == false) {
					std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
					_board[x][y] = piece;
					return 1;
				}
			}
		}
		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;
	} else {
		x_initial_position = x;
		y_initial_position = y;
		std::cout << "a\n";
		if (x != SIZE - 1 && y != SIZE - 1) { // Down/right
			_board[x][y] = '.';
			x += 1;
			y += 1;
			if (square_is_free(x, y) == false) {
				if (is_uppercase(_board[x][y]) == true) {
					std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
					_board[x][y] = piece;
					return 1;
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		std::cout << "b\n";
		if (x != SIZE - 1 && y != 0) { // Down/left
			_board[x][y] = '.';
			std::cout << x << y << "\n";

			x += 1;
			y -= 1;
			std::cout << x << y << "\n";
			if (square_is_free(x, y) == false) {
				std::cout << "d\n";
				if (is_uppercase(_board[x][y]) == true) {
					std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
					_board[x][y] = piece;
					return 1;
				}
			}
		}
		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;
	}
	return 0;
}

void Minichess::moves_pawn (int x, int y) {
	int x_initial_position;
	char piece = _board[x][y];

	x_initial_position = x;

	if (pawn_attacks(x, y) == 0) { // If pawn can't attack
		if (_turn == true && x != 0) { // Uppercase pawn moves
			_board[x][y] = '.';
			x -= 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;

				/** Appeller pawn_attacks
				 * Si après le déplacement c'est un roi, faire qqchose (pour que le roi s'échappe de l'échec)
				 * sinon, on ne fait rien
				 */

				//_board[x][y] = '.';
			}
		} else if (_turn == false && x != SIZE - 1) { // Lowercase pawn moves
			_board[x][y] = '.';
			x += 1;
			if (square_is_free(x, y) == true) {
				std::cout << "min c'est libre ('w ')\n";
				_board[x][y] = piece;




				//_board[x][y] = '.';
			}
		}
		//x = x_initial_position;                        ENLEVER LES COMMENTAIRES ICI
		//_board[x][y] = piece;
	}

	
}

bool Minichess::square_is_free (int x, int y) {
	if (_board[x][y] == '.') 
		return true;
	return false;
}

bool Minichess::is_uppercase (char piece) {
	if (piece >= 65 && piece <= 90)
		return true;
	return false;
}

void Minichess::select_piece () {
	int i, j;
	if (_turn == true) {
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (_board[i][j] == 'P') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_pawn(i, j);
				}
				if (_board[i][j] == 'R') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_rook(i, j);
				}
				if (_board[i][j] == 'B') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_bishop(i, j);
				}
				if (_board[i][j] == 'Q') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_queen(i, j);
				}
			}
		}
		_turn = false;
	} else {
		for (i = SIZE - 1; i >= 0; i--) {
			for (j = 0; j < SIZE; j++) {
				if (_board[i][j] == 'p') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_pawn(i, j);
				}
				if (_board[i][j] == 'r') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_rook(i, j);
				}
				if (_board[i][j] == 'b') {
					std::cout << _board[i][j] << " en i(x) : " << i << ", j(y) : " << j << "\n";
					moves_bishop(i, j);
				}
			}
		}
		_turn = true;
	}
	
}

void Minichess::playout () {
	int i = 0;
	while (i < 5) {
		std::cout << "Tour " << i << "\n";
		select_piece ();
		print_board();
		i++;
	}
}

void Minichess::number_piece (std::vector<Piece> &vector_piece) {
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (_board[i][j] != '.') {
				Piece current_piece(_board[i][j], i, j);
				vector_piece.push_back(current_piece);
			}
		}
	}

	std::cout << "Nombre de pièces totales : "<< vector_piece.size() << "\n";
	
	if (vector_piece.size() > 0) {
		for (i = 0; i < (int)vector_piece.size(); i++) {
			std::cout << vector_piece[i].get_piece() << vector_piece[i].get_x() << vector_piece[i].get_y() << "\n";
		}
	}
}


int main () {
	/*Minichess m;

	m._turn = true;

	m.create_board();
	//m.init_board();

	Piece p ('P', 3, 0);
	std::cout << p.get_piece() << p.get_x() << p.get_y() << "\n";
	//m.add_piece('k', 3, 2);
	m.add_piece('p', 1, 2);
	m.add_piece('p', 0, 2);

	m.add_piece('P', 2, 1);
	m.add_piece('P', 3, 0);
	//m.add_piece('P', 4, 4);
	//m.add_piece('K', 0, 4);

	std::cout << "Position initiale\n";
	m.print_board();

	m.playout();

	//m.select_piece();
	//m.print_board();
	*/

///////////////////////////////////////////////////////////////////:
	Minichess m;

	m._turn = true;

	m.create_board();
	//m.init_board();

	//Piece p ('P', 3, 0);
	//std::cout << p.get_piece() << p.get_x() << p.get_y() << "\n";
	//m.add_piece('k', 3, 2);
	//m.add_piece('p', 1, 2);
	//m.add_piece('p', 1, 0);
	m.add_piece('p', 0, 1);

	//m.add_piece('P', 1, 2);
	m.add_piece('Q', 3, 2);

	//m.add_piece('P', 4, 4);
	m.add_piece('K', 3, 4);

	std::cout << "Position initiale\n";
	m.print_board();

	//m.playout();

	m.select_piece();
	//m.print_board();


///////////////////
	int const number_piece = 20;
	std::vector<Piece> vector_piece;

	m.number_piece(vector_piece);

	std::cout << "\n";

	
	return 0;
}