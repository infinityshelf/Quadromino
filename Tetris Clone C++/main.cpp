// main.cpp
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GridController.hpp"
#include "TetrisPiece.hpp"

using namespace std;
int main(int argc, char const *argv[]) {
    bool save = false;
    bool load = false;
    const char loadFlag[] = {"-load"};
    const char saveFlag[] = {"-save"};
    if (argc == 3) {
        for (int i = 1; i < argc; i++) {
            if (std::strncmp(argv[i],saveFlag, 6) == 0) {
                std::cout << "Saving" << std::endl;
                save = true;
            }
            if (std::strncmp(argv[i],loadFlag, 6) == 0) {
                std::cout << "Loading" << std::endl;
                load = true;
            }
        }
    } else if (argc > 3) {
        std::cout << "Too many arguments!" << endl;
        return 0;
    }
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetris");
    static GridController *mainGrid = GridController::instance();
    if (load) {
        mainGrid->loadGridFromFile();
    }
    bool autoDrop = true;
    window.setFramerateLimit(60);
    TetrisPiece piece;
    piece.reset();
    piece.frameCounter = 0;
    bool spawnPiece = false;
    bool canInstantDrop = true;
    while (window.isOpen()) {
        piece.frameCounter++;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                if (save) {
                    mainGrid->saveGridToFile();
                }
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape or event.key.code == sf::Keyboard::Q) {
                    if (save) {
                        mainGrid->saveGridToFile();
                    }
                    window.close();
                } else {
                    if (event.key.code == sf::Keyboard::Left) {
                        piece.moveLeft();
                    }
                    else if (event.key.code == sf::Keyboard::Right) {
                        piece.moveRight();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        autoDrop = false;
                        piece.moveDown();
                        // frame counter to 0 to make it so that
                        // when the player presses down and their piece moves down
                        // it takes a second for the piece to move again automatically
                        piece.frameCounter = 0;
                    }
                    else if (event.key.code == sf::Keyboard::Up && canInstantDrop) {
                        int y = piece.row;
                        // move down
                        piece.moveDown();
                        while (y != piece.row) {
                            // keep moving down if position is still changing
                            y = piece.row;
                            piece.moveDown();
                        }
                        // instantly lock
                        piece.lock();
                        canInstantDrop = false;
                    }
                    else if (event.key.code == sf::Keyboard::D) {
                        piece.rotateClockwise();
                    }
                    else if (event.key.code == sf::Keyboard::A) {
                        piece.rotateCounterClockwise();
                    }
                    else if (event.key.code == sf::Keyboard::C) {
                        piece.reset();
                    }
                    else if (event.key.code == sf::Keyboard::Z) {
                        mainGrid->saveGridToFile();
                    }
                    else if (event.key.code == sf::Keyboard::X) {
                        mainGrid->loadGridFromFile();
                    }
                }
            } else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Down) {
                    autoDrop = true;
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    // released up
                    canInstantDrop = true;
                }
            }
        }
        if (piece.locked) {
            spawnPiece = true;
        }
        if (spawnPiece) {
            //piece.printGrid();
            piece.reset();
            spawnPiece = false;
        }
        window.clear();
        if (piece.frameCounter % 60 == 59) {
            piece.frameCounter %= 60;
            if (autoDrop) {
                piece.moveDown();
            }
        }
        piece.drawToWindow(window);
        mainGrid->drawToWindow(window);
        window.display();
    }

    return EXIT_SUCCESS;
}
