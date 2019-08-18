#include "minichess.hpp"

void Minichess::moves_king (int x, int y) {
	int x_initial_position, y_initial_position;
	char piece = _board[x][y];

	x_initial_position = x;
	y_initial_position = y;
	std::cout << "ICI en x : " << x << ", y : " << y << "\n";
	std::cout << "ICI en x_initial_position : " << x_initial_position << ", y_initial_position : " << y_initial_position << "\n";

	if (king_attacks(x, y) == 0) { // If knight can't attack
		std::cout << "King haut\n";
		if (x != 0) { // Moves up
			_board[x][y] = '.';
			x -= 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				king_attacks(x, y);

				_board[x][y] = '.';
			}
		}
		std::cout << _board[x][y] << " en x : " << x << ", y : " << y << "\n";

		x = x_initial_position;
		y = y_initial_position;
		std::cout << "King haut/droite\n";
		std::cout << _board[x][y] << " en x : " << x << ", y : " << y << "\n";

		if (x != 0 && y != SIZE - 1) { // Moves up/right
			_board[x][y] = '.';
			x -= 1;
			y += 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				king_attacks(x, y);

				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		std::cout << "King droite\n";

		if (y != SIZE - 1) { // Moves right
			_board[x][y] = '.';
			y += 1;
			std::cout << _board[x][y] << " en x : " << x << ", y : " << y << "\n";
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				king_attacks(x, y);

				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		std::cout << "King bas/droite\n";

		if (x != SIZE - 1 && y != SIZE - 1) { // Moves right/down
			_board[x][y] = '.';
			x += 1;
			y += 1;
			std::cout << _board[x][y] << " en x : " << x << ", y : " << y << "\n";
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				king_attacks(x, y);

				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		std::cout << "King bas\n";
		if (x != SIZE - 1) { // Moves down
			_board[x][y] = '.';
			x += 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				king_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		std::cout << "King bas/gauche\n";
		if (x != SIZE - 1 && y != 0) { // Moves down/left
			_board[x][y] = '.';
			x += 1;
			y -= 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				king_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		std::cout << "King gauche\n";
		if (y != 0) { // Moves left
			_board[x][y] = '.';
			y -= 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				king_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		std::cout << "King haut/gauche\n";
		if (x != 0 && y != 0) { // Moves left/up
			_board[x][y] = '.';
			x -= 1;
			y -= 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				king_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;
	}
}

void Minichess::moves_knight (int x, int y) {
	int x_initial_position, y_initial_position;
	char piece = _board[x][y];

	x_initial_position = x;
	y_initial_position = y;
	std::cout << "ICI en x : " << x << ", y : " << y << "\n";
	std::cout << "ICI en x_initial_position : " << x_initial_position << ", y_initial_position : " << y_initial_position << "\n";

	if (knight_attacks(x, y) == 0) { // If knight can't attack
		std::cout << "A\n";
		if (x > 1 && y < SIZE - 1) { // Moves 2*up/1*right
			_board[x][y] = '.';
			x -= 2;
			y += 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				knight_attacks(x, y);

				_board[x][y] = '.';
			}
		}
		std::cout << _board[x][y] << " en x : " << x << ", y : " << y << "\n";

		x = x_initial_position;
		y = y_initial_position;
		std::cout << "B\n";
		std::cout << _board[x][y] << " en x : " << x << ", y : " << y << "\n";

		if (x != 0 && y < SIZE - 2) { // Moves 1*up/2*right
			_board[x][y] = '.';
			x -= 1;
			y += 2;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				knight_attacks(x, y);

				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		if (x != SIZE - 1 && y < SIZE - 2) { // Moves 2*right/1*down
			_board[x][y] = '.';
			x += 1;
			y += 2;
			std::cout << _board[x][y] << " en x : " << x << ", y : " << y << "\n";
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				knight_attacks(x, y);

				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		if (x < SIZE - 2 && y != SIZE - 1) { // Moves 1*right/2*down
			_board[x][y] = '.';
			x += 2;
			y += 1;
			std::cout << _board[x][y] << " en x : " << x << ", y : " << y << "\n";
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				knight_attacks(x, y);

				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		std::cout << "C\n";
		if (x < SIZE - 2 && y != 0) { // Moves 2*down/1*left
			_board[x][y] = '.';
			x += 2;
			y -= 1;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				knight_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		if (x != SIZE - 1 && y > 1) { // Moves 1*down/2*left
			_board[x][y] = '.';
			x += 1;
			y -= 2;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				knight_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		std::cout << "D\n";
		if (x != 0 && y > 1) { // Moves 2*left/1*up
			_board[x][y] = '.';
			x -= 1;
			y -= 2;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				knight_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;

		if (x > 1 && y != 0) { // Moves 1*left/2*up
			_board[x][y] = '.';
			x -= 1;
			y -= 2;
			if (square_is_free(x, y) == true) {
				std::cout << "MAJ C'EST LIBRE (¤_ ¤)\n";
				_board[x][y] = piece;
				print_board();
				knight_attacks(x, y);


				_board[x][y] = '.';
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;
	}
}

void Minichess::moves_bishop (int x, int y) {
	int x_initial_position, y_initial_position;
	char piece = _board[x][y];

	x_initial_position = x;
	y_initial_position = y;
	std::cout << "ICI en x : " << x << ", y : " << y << "\n";
	std::cout << "ICI en x_initial_position : " << x_initial_position << ", y_initial_position : " << y_initial_position << "\n";

	if (bishop_attacks(x, y) == 0) { // If bishop can't attack
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

void Minichess::moves_queen (int x, int y) { // Queen acts like a rook and a bishop
	moves_rook(x, y);
	moves_bishop(x, y);
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