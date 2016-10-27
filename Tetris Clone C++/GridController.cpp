#import "GridController.hpp"
#import <iostream>

const int windowWidth = pixels * 10;
const int windowHeight = pixels * 22;
const bool debug = true;
const int pixels = 32.0f;
const int max_rows = 22;
const int max_columns = 10;

GridController * GridController::s_instance = nullptr;
sf::RenderWindow * GridController::m_windowref = nullptr;

GridController* GridController::instance() {
    static GridController instance;
    std::cout << "instance pointer = " << &instance;
    return &instance;
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
    if (row >= 0 && row < max_rows && col >= 0 && col < max_columns) {
        this->grid[col][row] = occupied;
    }
    //this->printGrid();
}

void GridController::printGrid() {
    std::cout << std::endl;
    for (int row = 0; row < max_rows; row++) {
        for (int col = 0; col < max_columns; col++) {
            if (col == 0) {
                std::cout << "|";
            }
            std::cout << ((this->grid[col][row]) ? "$" : "_");
            if (col == 9) {
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
