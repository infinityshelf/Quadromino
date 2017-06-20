CFLAGS = -std=c++14 -Wall -Winit-self -Wextra -Weffc++ -pedantic -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -flto -Wodr -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -Werror
INCLUDE_SFML = -I/usr/local/include
LIB_SFML = -L/usr/local/lib -lsfml-window -lsfml-system -lsfml-graphics 
all:
	make run

run: Tetris
	./Tetris

Tetris: main.o TetrisPiece.o GridController.o Monomino.o
	g++ $(CFLAGS) main.o TetrisPiece.o GridController.o Monomino.o -o Tetris $(LIB_SFML)

main.o: main.cpp TetrisPiece.hpp GridController.hpp TetrominoTypes.hpp Monomino.hpp
	g++ $(CFLAGS) -c main.cpp $(INCLUDE_SFML)

TetrisPiece.o: TetrisPiece.cpp TetrisPiece.hpp GridController.hpp TetrominoTypes.hpp
	g++ $(CFLAGS) -c TetrisPiece.cpp $(INCLUDE_SFML)

GridController.o: GridController.cpp GridController.hpp TetrominoTypes.hpp
	g++ $(CFLAGS) -c GridController.cpp $(INCLUDE_SFML)

Monomino.o: Monomino.cpp Monomino.hpp TetrisPiece.hpp TetrominoTypes.hpp
	g++ $(CFLAGS) -c Monomino.cpp $(INCLUDE_SFML)

clean:
	rm *.o
	rm Tetris

recompile:
	make clean
	make Tetris
