#include "minichess.hpp"

Piece::Piece(char piece, int x, int y) {
	this->_piece = piece;
	this->_x = x;
	this->_y = y;
}

Piece::~Piece() {}

char Piece::get_piece () {
	return _piece;
}

void Piece::set_piece (char piece) {
	_piece = piece;
}

int Piece::get_x () {
	return _x;
}

void Piece::set_x (int x) {
	_x = x;
}

int Piece::get_y () {
	return _y;
}

void Piece::set_y (int y) {
	_y = y;
}