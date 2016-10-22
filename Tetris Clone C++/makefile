CFLAGS = -Wall

all: main.o TetrisPiece.o GridController.o
	g++ $(CFLAGS) main.o TetrisPiece.o GridController.o -o Tetris.exe -lsfml-graphics -lsfml-window -lsfml-system
	./Tetris

main.o: main.cpp TetrisPiece.hpp GridController.hpp
	g++ $(CFLAGS) -c main.cpp

TetrisPiece.o: TetrisPiece.cpp TetrisPiece.hpp GridController.hpp
	g++ $(CFLAGS) -c TetrisPiece.cpp

GridController.o: GridController.cpp GridController.hpp
	g++ $(CFLAGS) -c GridController.cpp

