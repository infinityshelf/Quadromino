#import "GridController.hpp"
#import <iostream>

const int windowWidth = pixels * 10;
const int windowHeight = pixels * 22;
const bool debug = true;
const int pixels = 32.0f;
const int rows = 22;
const int columns = 10;

GridController& GridController::instance() {
    static GridController instance;
    std::cout << "instance pointer = " << &instance << std::endl;
    return instance;
}

GridController::GridController() {
    // for (int i = 0; i < rows*columns; i++) {
    //     this->grid[0][i] = false;
    // }
}

GridController::~GridController() {}

bool GridController::isSpaceOccupied(int row, int col) {
    return this->grid[col][row];
}

void GridController::setSpaceOccupied(int row, int col, bool occupied) {
    if (row >= 0 && row < rows && col >= 0 && col < columns) {
        this->grid[col][row] = occupied;
    }
    this->printGrid();
}

void GridController::printGrid() {
    std::cout << "~~~~~~~~~~" << std::endl;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            std::cout << ((this->grid[col][row]) ? "@" : "_");
            if (col % 10 == 9) {
                std::cout << std::endl;
            }
        }
    }
}