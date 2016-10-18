CFLAGS = -Wall

all: tetris.o TetrisPiece.o
	g++ $(CFLAGS) tetris.o TetrisPiece.o -o Tetris -lsfml-graphics -lsfml-window -lsfml-system
	./Tetris
tetris.o: tetris.cpp
	g++ $(CFLAGS) -c tetris.cpp
TetrisPiece.o: TetrisPiece.cpp
	g++ $(CFLAGS) -c TetrisPiece.cpp