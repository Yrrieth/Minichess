#include "minichess.hpp"

int Minichess::king_attacks (int x, int y) {
	int x_initial_position, y_initial_position;
	char piece = _board[x][y];

		x_initial_position = x;
		y_initial_position = y;
		if (x != 0) { // Up
			_board[x][y] = '.';
			x -= 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x != 0 && y != SIZE - 1) { // Up/right
			_board[x][y] = '.';
			x -= 1;
			y += 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (y != SIZE - 1) { // right
			_board[x][y] = '.';
			y += 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x != SIZE - 1 && y != SIZE - 1) { // right/down
			_board[x][y] = '.';
			x += 1;
			y += 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x != SIZE - 1) { // down
			_board[x][y] = '.';
			x += 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				} 
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x != SIZE - 1 && y != 0) { // down/left
			_board[x][y] = '.';
			x += 1;
			y -= 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				} 
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (y != 0) { // left
			_board[x][y] = '.';
			y -= 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}
		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x != 0 && y != 0) { // left/up
			_board[x][y] = '.';
			x -= 1;
			y -= 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}
		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

	return 0;
}

int Minichess::knight_attacks (int x, int y) {
	int x_initial_position, y_initial_position;
	char piece = _board[x][y];

		x_initial_position = x;
		y_initial_position = y;
		if (x > 1 && y != SIZE - 1) { // 2*Up/1*right
			_board[x][y] = '.';
			x -= 2;
			y += 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x != 0 && y < SIZE - 2) { // 1*Up/2*right
			_board[x][y] = '.';
			x -= 1;
			y += 2;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x != SIZE - 1 && y < SIZE - 2) { // 2*right/1*down
			_board[x][y] = '.';
			x += 1;
			y += 2;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x < SIZE - 2 && y != SIZE - 1) { // 1*right/2*down
			_board[x][y] = '.';
			x += 2;
			y += 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x < SIZE - 2 && y != 0) { // 2*down/1*left
			_board[x][y] = '.';
			x += 2;
			y -= 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				} 
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x != SIZE - 1 && y > 1) { // 1*down/2*left
			_board[x][y] = '.';
			x += 1;
			y -= 2;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				} 
			}
		}

		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x != 0 && y > 1) { // 2*left/1*up
			_board[x][y] = '.';
			x -= 1;
			y -= 2;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}
		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

		if (x > 1 && y != 0) { // 1*left/2*up
			_board[x][y] = '.';
			x -= 2;
			y -= 1;
			if (square_is_free(x, y) == false) {
				if (_turn == true) {
					if (is_uppercase(_board[x][y]) == false) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;	
					}
				} 
				if (_turn == false) {
					if (is_uppercase(_board[x][y]) == true) {
						std::cout << "Le " << _board[x][y] << " en " << x << ","<< y << " est attaqué\n";
						_board[x][y] = piece;
						return 1;
					}
				}
			}
		}
		x = x_initial_position;
		y = y_initial_position;
		_board[x][y] = piece;

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