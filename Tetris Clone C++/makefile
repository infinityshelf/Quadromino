CFLAGS = -std=c++14 -Wall -Winit-self -Wextra -Weffc++ -pedantic -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -flto -Wodr -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -Werror
# CFLAGS = -Wall
all:
	make run

run:
	make no-run
	./Tetris.exe #-load #-save

no-run: main.o TetrisPiece.o GridController.o Monomino.o
	g++ $(CFLAGS) main.o TetrisPiece.o GridController.o Monomino.o -o Tetris.exe -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp TetrisPiece.hpp GridController.hpp TetrominoTypes.hpp Monomino.hpp
	g++ $(CFLAGS) -c main.cpp

TetrisPiece.o: TetrisPiece.cpp TetrisPiece.hpp GridController.hpp TetrominoTypes.hpp
	g++ $(CFLAGS) -c TetrisPiece.cpp

GridController.o: GridController.cpp GridController.hpp TetrominoTypes.hpp
	g++ $(CFLAGS) -c GridController.cpp

Monomino.o: Monomino.cpp Monomino.hpp TetrisPiece.hpp TetrominoTypes.hpp
	g++ $(CFLAGS) -c Monomino.cpp

clean:
	rm *.o
	rm *.exe

recompile:
	make clean
	make wo-run
