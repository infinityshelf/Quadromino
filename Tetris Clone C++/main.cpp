// main.cpp
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GridController.hpp"
#include "TetrisPiece.hpp"

bool spawnPiece = false;
bool canInstantDrop = true;
bool canHold = true;
bool autoDrop = true;

TetrominoType heldType = TETROMINO_TYPE_NONE;


void saveGridToFile() {
    FILE *fp = fopen(fileName, "wb");
    size_t length = ROWS * COLUMNS;
    char *gridString = new char[length];
    GridController* instance = GridController::instance();
    for (int i = 0; i < (int) length; i++) {
        gridString[i] = GridController::characterForType(instance->grid[0][i]);
    }
    char stupidvar = GridController::characterForType(heldType);
    if (fp != NULL) {
        fseek(fp, SEEK_SET, 0);
        fwrite(gridString, sizeof(char), length, fp);
        fwrite(&score, sizeof(score), 1, fp);
        fwrite(&totalLinesCleared, sizeof(totalLinesCleared), 1, fp);
        fwrite(&level, sizeof(level), 1, fp);
        fwrite(&stupidvar, sizeof(stupidvar), 1, fp);
        fclose(fp);
    } else {
        std::cout << "COULD NOT OPEN FILE: " << fileName << "\007" << std::endl;
    }
    delete[] gridString;
}

void loadGridFromFile() {
    FILE *fp = fopen(fileName, "rb");
    size_t length = ROWS * COLUMNS;
    char *gridString = new char[length];
    GridController* instance = GridController::instance();
    char stupidvar;
    if (fp != NULL) {
        fseek(fp, SEEK_SET, 0);
        fread(gridString, sizeof(char), length, fp);
        fread(&score, sizeof(score), 1, fp);
        fread(&totalLinesCleared, sizeof(totalLinesCleared), 1, fp);
        fread(&level, sizeof(level), 1, fp);
        fread(&stupidvar, sizeof(stupidvar), 1, fp);
        heldType = GridController::typeForCharacter(stupidvar);
        for (int i = 0; i < (int) length; i++) {
            instance->grid[0][i] = GridController::typeForCharacter(gridString[i]);
        }
        //this->printGrid();
        fclose(fp);
    } else {
        std::cout << "COULD NOT OPEN FILE: " << fileName <<  "\007" << std::endl;
    }
    delete[] gridString;
}


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
    window.setFramerateLimit(60);

    sf::Image icon;
    if (icon.loadFromFile("TLogo.png")) {
        window.setIcon(1024,1024, icon.getPixelsPtr());
    } else {
        std::cout << "unable to open file";
    }


    static GridController *mainGrid = GridController::instance();
    if (load) {
        loadGridFromFile();
    }
    TetrisPiece piece;
    piece.reset();
    while (window.isOpen()) {
        piece.frameCounter++;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed or (
                    event.type == sf::Event::KeyPressed and (
                        event.key.code == sf::Keyboard::Escape or
                        event.key.code == sf::Keyboard::Q
                    ))) {
                if (save) {
                    saveGridToFile();
                }
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
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
                    // although the player can still time it so that the autodrop happens
                    // and then they press down
                }
                else if (event.key.code == sf::Keyboard::Up and canInstantDrop) {
                    piece.castDown(true);
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
                    saveGridToFile();
                }
                else if (event.key.code == sf::Keyboard::X) {
                    loadGridFromFile();
                }
                else if (event.key.code == sf::Keyboard::E and canHold) {
                    if (heldType == TETROMINO_TYPE_NONE) {
                        heldType = piece.getType();
                        piece.reset();
                        //just to make sure
                        spawnPiece = false;
                    } else {
                        auto temp = piece.getType();
                        piece.resetWithType(heldType);
                        heldType = temp;
                        canHold = false;
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
            canHold = true;
        }
        window.clear();
        unsigned int difficultyFrame;
        if (level < 20) {
            difficultyFrame = 20 + ((20-level) * 2);
        } else {
            difficultyFrame = 20;
        }
        piece.frameCounter %= difficultyFrame;
        if (piece.frameCounter == difficultyFrame-1 and autoDrop) {
            piece.moveDown();
        }
        piece.drawToWindow(window);
        mainGrid->checkRows();
        mainGrid->drawToWindow(window);
        window.display();
    }

    return EXIT_SUCCESS;
}
