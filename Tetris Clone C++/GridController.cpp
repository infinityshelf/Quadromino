#include "GridController.hpp"
#include "TetrisPiece.hpp"
#include <iostream>
#include <cassert>

const int windowWidth = pixels * COLUMNS;
const int windowHeight = pixels * ROWS;
const bool debug = true;
const int pixels = 32.0f;

// typedef enum TETROMINO_TYPES TetrominoType;

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
    // this->grid[COLUMNS][ROWS] = {TETROMINO_TYPE_NONE};
    for (int y = 0; y < ROWS; y++) {
        // for (int j = 0; i < 22; j++) {
        for (int x = 0; x < COLUMNS; x++) {
            this->grid[y][x] = TETROMINO_TYPE_NONE;
        }
    }
}

GridController::~GridController() {}

bool GridController::isSpaceOccupied(int x, int y) {
    bool occupado = false;
    if (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS) {
        occupado = (this->grid[y][x] != TETROMINO_TYPE_NONE);
    }
    return occupado;
}

void GridController::setSpaceOccupied(int x, int y, TetrominoType type) {
    if (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS) {
        std::cout << "setspace called" << std::endl;
        this->grid[y][x] = type;
        assert(this->grid[y][x] != TETROMINO_TYPE_NONE);
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
            TetrominoType tetrominoType = this->grid[y][x];
            // std::cout << static_cast<int>(TetrominoType);
            switch(tetrominoType) {
                case TETROMINO_TYPE_O: {
                    // std::cout << "TetrominoType is O";
                    place = 'O';
                    break;
                }
                case TETROMINO_TYPE_I: {
                    // std::cout << "TetrominoType is I";
                    place = 'I';
                    break;
                }
                case TETROMINO_TYPE_L: {
                    // std::cout << "TetrominoType is L";
                    place = 'L';
                    break;
                }
                case TETROMINO_TYPE_J: {
                    // std::cout << "TetrominoType is J";
                    place = 'J';
                    break;
                }
                case TETROMINO_TYPE_S: {
                    // std::cout << "TetrominoType is S";
                    place = 'S';
                    break;
                }
                case TETROMINO_TYPE_Z: {
                    // std::cout << "TetrominoType is Z";
                    place = 'Z';
                    break;
                }
                case TETROMINO_TYPE_T: {
                    // std::cout << "TetrominoType is T";
                    place = 'T';
                    break;
                }
                case TETROMINO_TYPE_MAX:{}
                case TETROMINO_TYPE_NONE: {
                    // std::cout << "TetrominoType is None";
                    place = '_';
                    break;
                }
                default: {
                    place = '#';
                    std::cout << tetrominoType;
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

void GridController::draw() {
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLUMNS; ++x) {
            sf::RectangleShape shape = Monomino::rectangleShapeForType(this->grid[y][x]);
            shape.setPosition(x*pixels, y*pixels);
            if (this->grid[y][x] != TETROMINO_TYPE_NONE) {
                this->m_windowref->draw(shape);
            }
        }
    }
}



