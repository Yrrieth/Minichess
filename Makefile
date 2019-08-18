CXX=g++
SRC=minichess.cpp piece.cpp move_piece.cpp piece_attack.cpp
OBJ=$(SRC:.c=.o)
CXXFLAGS=-O3 -std=c++14 -Wall

chess:	$(OBJ) minichess.hpp
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o:	%.c
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm chess