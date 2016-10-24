#include "GridController.hpp"
// #include "TetrisPiece.hpp"
#include <iostream>

const int windowWidth = pixels * 10;
const int windowHeight = pixels * 22;
const bool debug = true;
const int pixels = 32.0f;
#define ROWS 22
#define COLUMNS 10

typedef enum TETRONIMO_TYPES TetronimoType;

GridController * GridController::s_instance = nullptr;
sf::RenderWindow * GridController::m_windowref = nullptr;


GridController* GridController::instance() {
    // static GridController instance = GridController();
    static GridController instance = GridController();
    std::cout << "instance pointer = " << &instance << std::endl;
    return &instance;
}

GridController::GridController() {
    // for (int i = 0; i < ROWS*COLUMNS; i++) {
    //     this->grid[0][i] = false;
    // }
    // this->grid[10][22] = {TETRONIMO_TYPE_NONE};
    for (int y = 0; y < 22; y++) {
        // for (int j = 0; i < 22; j++) {
        for (int x = 0; x < 10; x++) {
            this->grid[y][x] = TETRONIMO_TYPE_NONE;
        }
    }
}

GridController::~GridController() {}

bool GridController::isSpaceOccupied(int x, int y) {
    return (this->grid[y][x] != TETRONIMO_TYPE_NONE);
}

void GridController::setSpaceOccupied(int x, int y, TetronimoType type) {
    if (x >= 0 && x < ROWS && y >= 0 && y < COLUMNS) {
        this->grid[y][x] = type;
    }
    //this->printGrid();
}

void GridController::printGrid() {
    std::cout << std::endl;
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            if (x == 0) {
                std::cout << "|";
            }
            char place = '_';
            TetronimoType tetronimoType = this->grid[y][x];
            switch(tetronimoType) {
                case TETRONIMO_TYPE_O: {
                    // std::cout << this->grid[y][x];
                    place = 'O';
                    break;
                }
                case TETRONIMO_TYPE_I: {
                    place = 'I';
                    break;
                }
                case TETRONIMO_TYPE_L: {
                    place = 'L';
                    break;
                }
                case TETRONIMO_TYPE_J: {
                    place = 'J';
                    break;
                }
                case TETRONIMO_TYPE_S: {
                    place = 'S';
                    break;
                }
                case TETRONIMO_TYPE_Z: {
                    place = 'Z';
                    break;
                }
                case TETRONIMO_TYPE_T: {
                    place = 'T';
                    break;
                }
                case TETRONIMO_TYPE_NONE: {
                    place = '_';
                    break;
                }
                default: {
                    place = '#';
                    std::cout << tetronimoType;
                    break;
                }
            }
            std::cout << place;
            if (x == 9) {
                std::cout << "|" << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

void GridController::provideWindow(sf::RenderWindow * window) {
    this->m_windowref = window;
}

sf::RenderWindow * GridController::window_instance() {
    return this->m_windowref;
}
