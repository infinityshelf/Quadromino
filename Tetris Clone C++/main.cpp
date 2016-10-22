// main.cpp
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GridController.hpp"
#include "TetrisPiece.hpp"

using namespace std;

int main()
{
    int frameCounter = 0;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetris");
    static GridController *mainGrid = GridController::instance();
    mainGrid->provideWindow(&window);
    mainGrid->printGrid();
    window.setFramerateLimit(60);
    TetrisPiece piece;
    piece.updatePosition(0,0);
    piece.setType(TETRONIMO_TYPE_Z);
    
    bool autoDrop = true;
    // bool spawnPiece = false;
    while (window.isOpen()) {
        frameCounter++;
    
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
                        piece.moveLeft();
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                    
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
        //     spawnPiece = true;
        // }
        // if (spawnPiece) {
        //     piece.stick();
        //     TetronimoType nextpiece = mainGrid->queue->peek();
        //     piece.reset_with_type(nextpiece);
        //     spawnPiece = false;
        // }
        window.clear();
        if (frameCounter % 60 == 59) {
            frameCounter %= 60;
            if (autoDrop) {
                piece.moveDown();
            }
        }
        piece.draw();
        window.display();
    }

    return EXIT_SUCCESS;
}
