// main.cpp
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GridController.hpp"
#include "TetrisPiece.hpp"

using namespace std;

int main()
{
    cout << "size of uint8_t" << sizeof(uint8_t) << endl;
    int frameCounter = 0;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetris");
    
    static GridController &mainGrid = GridController::instance();
    mainGrid.printGrid();
    
    window.setFramerateLimit(60);
    
    TetrisPiece piece(mainGrid, window);
    piece.updatePosition(0,0);
    piece.setType(TETRONIMO_TYPE_Z);
    
    bool autoDrop = true;
    
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
                    }
                }
            } else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Down) {
                    autoDrop = true;
                }
            }
        }
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
