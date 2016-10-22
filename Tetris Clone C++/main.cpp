// main.cpp
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "TetrisPiece.hpp"
#include "GridController.hpp"

using namespace std;
//using namespace sf;

int main()
{
    // cout << "size of uint8_t" << sizeof(uint8_t) << endl;
    int frameCounter = 0;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetris");
    static GridController *mainGrid = GridController::instance();
    mainGrid->provideWindow(&window);
    mainGrid->printGrid();
    window.setFramerateLimit(60);
    TetrisPiece piece;
    // piece.provideGridController(mainGrid);
    // piece.provideWindow(&window);
    piece.updatePosition(0,0);
    piece.setType(TETRONIMO_TYPE_Z);
    bool autoDrop = true;
    // bool spawnPiece = false;
    while (window.isOpen()) {
        frameCounter++;
        //(debug) ? cout << "frame: \n" << frameCounter : NULL;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else {
                    if (event.key.code == sf::Keyboard::Left) {
                        (debug) ? cout << "Left\n" : NULL;
                        piece.moveLeft();
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        (debug) ? cout << "Right\n" : NULL;
                        piece.moveRight();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        autoDrop = false;
                        piece.moveDown();
                        // frame counter to 0 to make it so that
                        // when the player presses down and their piece moves down
                        // it takes a second for the piece to move again automatically
                        frameCounter = 0;
                    }
                }
            } else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Down) {
                    autoDrop = true;
                }
            }
        }
        // if (piece.row >= 18) {
        //     // piece.destroy();
        //     spawnPiece = true;
        // }
        // if (spawnPiece) {
        //     piece = TetrisPiece();
        //     spawnPiece = false;
        // }
        window.clear();
        if (frameCounter % 60 == 59) {
            frameCounter %= 60;
            if (autoDrop) {
                std::cout << "auto drop" << endl;
                piece.moveDown();
            } else {
                std::cout << "didn't auto drop" << std::endl;
            }
        }
        piece.draw();
        window.display();
    }

    return EXIT_SUCCESS;
}
