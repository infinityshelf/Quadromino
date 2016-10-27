#include "GridController.hpp"
#include "TetrisPiece.hpp"
#include <iostream>
#include <cassert>

const int windowWidth = pixels * COLUMNS;
const int windowHeight = pixels * ROWS;
const bool debug = true;
const int pixels = 32.0f;

// typedef enum TETRONIMO_TYPES TetronimoType;

GridController * GridController::s_instance = nullptr;
sf::RenderWindow * GridController::m_windowref = nullptr;


GridController* GridController::instance() {
    // static GridController instance = GridController();
    static GridController instance = GridController();
    // std::cout << "instance pointer = " << &instance << std::endl;
    return &instance;
}

GridController::GridController() {
    // for (int i = 0; i < ROWS*COLUMNS; i++) {
    //     this->grid[0][i] = false;
    // }
    // this->grid[COLUMNS][ROWS] = {TETRONIMO_TYPE_NONE};
    for (int y = 0; y < ROWS; y++) {
        // for (int j = 0; i < 22; j++) {
        for (int x = 0; x < COLUMNS; x++) {
            this->grid[y][x] = TETRONIMO_TYPE_NONE;
        }
    }
}

GridController::~GridController() {}

bool GridController::isSpaceOccupied(int x, int y) {
    return (this->grid[y][x] != TETRONIMO_TYPE_NONE);
}

void GridController::setSpaceOccupied(int x, int y, TetronimoType type) {
    if (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS) {
        std::cout << "setspace called" << std::endl;
        this->grid[y][x] = type;
        assert(this->grid[y][x] != TETRONIMO_TYPE_NONE);
    }
    // std::cout << "setspace called" << std::endl;
    this->printGrid();
}

void GridController::printGrid() {

    // std::cout << std::endl;
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            if (x == 0) {
                std::cout << "|";
            }
            char place;
            TetronimoType tetronimoType = this->grid[y][x];
            // std::cout << static_cast<int>(tetronimoType);
            switch(tetronimoType) {
                case TETRONIMO_TYPE_O: {
                    // std::cout << "tetronimoType is O";
                    place = 'O';
                    break;
                }
                case TETRONIMO_TYPE_I: {
                    // std::cout << "tetronimoType is I";
                    place = 'I';
                    break;
                }
                case TETRONIMO_TYPE_L: {
                    // std::cout << "tetronimoType is L";
                    place = 'L';
                    break;
                }
                case TETRONIMO_TYPE_J: {
                    // std::cout << "tetronimoType is J";
                    place = 'J';
                    break;
                }
                case TETRONIMO_TYPE_S: {
                    // std::cout << "tetronimoType is S";
                    place = 'S';
                    break;
                }
                case TETRONIMO_TYPE_Z: {
                    // std::cout << "tetronimoType is Z";
                    place = 'Z';
                    break;
                }
                case TETRONIMO_TYPE_T: {
                    // std::cout << "tetronimoType is T";
                    place = 'T';
                    break;
                }
                case TETRONIMO_TYPE_NONE: {
                    // std::cout << "tetronimoType is None";
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
