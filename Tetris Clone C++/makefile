CFLAGS = -std=c++14 -Wall -Winit-self -Wextra -Weffc++ -Werror -pedantic -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -flto -Wodr -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral
# CFLAGS = -Wall

all: main.o TetrisPiece.o GridController.o
	make wo-run
	./Tetris.exe

wo-run: main.o TetrisPiece.o GridController.o
	g++ $(CFLAGS) main.o TetrisPiece.o GridController.o -o Tetris.exe -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp TetrisPiece.hpp GridController.hpp
	g++ $(CFLAGS) -c main.cpp

TetrisPiece.o: TetrisPiece.cpp TetrisPiece.hpp GridController.hpp
	g++ $(CFLAGS) -c TetrisPiece.cpp

GridController.o: GridController.cpp GridController.hpp
	g++ $(CFLAGS) -c GridController.cpp

clean:
	rm *.o
	rm *.exe

recompile:
	make clean
	make wo-run
