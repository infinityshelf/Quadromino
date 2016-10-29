#include "GridController.hpp"
#include "TetrisPiece.hpp"
#include <iostream>
#include <cassert>

const int windowWidth = pixels * COLUMNS;
const int windowHeight = pixels * ROWS;
const bool debug = true;
const int pixels = 32.0f;
const char fileName[] = "grid.out";

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
        //assert(this->grid[y][x] != TETROMINO_TYPE_NONE);
    }
    // std::cout << "setspace called" << std::endl;
    this->printGrid();
}

char GridController::characterForType(TetrominoType type) {
    char place;
    switch(type) {
        case TETROMINO_TYPE_O: {
            place = 'O';
            break;
        }
        case TETROMINO_TYPE_I: {
            place = 'I';
            break;
        }
        case TETROMINO_TYPE_L: {
            place = 'L';
            break;
        }
        case TETROMINO_TYPE_J: {
            place = 'J';
            break;
        }
        case TETROMINO_TYPE_S: {
            place = 'S';
            break;
        }
        case TETROMINO_TYPE_Z: {
            place = 'Z';
            break;
        }
        case TETROMINO_TYPE_T: {
            place = 'T';
            break;
        }
        case TETROMINO_TYPE_MAX:{}
        case TETROMINO_TYPE_NONE: {
            place = '_';
            break;
        }
        default: {
            place = '#';
            std::cout << type;
            break;
        }
    }
    return place;

}

TetrominoType GridController::typeForCharacter(char place) {
    std::cout << "WARNING: UNTESTED" << std::endl;
    TetrominoType type = TETROMINO_TYPE_NONE;
    switch(place) {
        case 'O': {
            type = TETROMINO_TYPE_O;
            break;
        }
        case 'I': {
            type = TETROMINO_TYPE_I;
            break;
        }
        case 'L': {
            type = TETROMINO_TYPE_L;
            break;
        }
        case 'J': {
            type = TETROMINO_TYPE_J;
            break;
        }
        case 'S': {
            type = TETROMINO_TYPE_S;
            break;
        }
        case 'Z': {
            type = TETROMINO_TYPE_Z;
            break;
        }
        case 'T': {
            type = TETROMINO_TYPE_T;
            break;
        }
        case '_': {
            type = TETROMINO_TYPE_NONE;
            break;
        }
    }
    return type;

}

void GridController::printGrid() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            TetrominoType tetrominoType = this->grid[y][x];
            char place = GridController::characterForType(tetrominoType);
            std::cout << place;
            if (x == 9) {
                std::cout << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

void GridController::saveGridToFile() {
    FILE *fp = fopen(fileName, "w+");
    std::cout << "Attempting to open file: " << fileName << std::endl;
    int length = ROWS * COLUMNS;
    char *gridString = (char *)malloc(sizeof(char) * length);
    for (int i = 0; i < length; i++) {
        gridString[i] = GridController::characterForType(this->grid[0][i]);
    }
    if (fp != NULL) {
        fwrite(gridString, sizeof(char), length, fp);
        fclose(fp);
        std::cout << "Close file " << fileName << std::endl;
    } else {
        std::cout << "COULD NOT OPEN FILE" << fileName << "\007" << std::endl;
    }
    free(gridString);

}

void GridController::provideWindow(sf::RenderWindow * window) {
    this->m_windowref = window;
}

sf::RenderWindow * GridController::window_instance() {
    return this->m_windowref;
}

void GridController::draw() {
    this->checkRows();
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

void GridController::checkRows() {
    for (int row = 0; row < ROWS; row++) {
        bool cleared = true;
        for (int col = 0; col < COLUMNS; col++) {
            if (!this->isSpaceOccupied(col, row)) {
                cleared = false;
            }
        }
        if (cleared == true) {
            this->clearRow(row);
            //TODO method not done
            //this->shiftRowsAbove(row);
        }
    }    
}

void GridController::clearRow(int rowToClear) {
    for (int col = 0; col < COLUMNS; col++) {
        this->setSpaceOccupied(col, rowToClear, TETROMINO_TYPE_NONE);
    }
}

void GridController::shiftRowsAbove(int clearedRow) {
    std::cout << "TODO: THIS CLEARS THE WHOLE GRID, FIX BUG" << std::endl;
    //assert(0);
    if (clearedRow < ROWS) {
        for (int row = clearedRow; row > 0; row--) {
            for (int col = 0; col < COLUMNS; col++) {
                this->setSpaceOccupied(col, row, this->grid[col][row-1]);
            }
        }
    }
}



