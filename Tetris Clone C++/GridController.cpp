#import "GridController.hpp"
#import <iostream>

const int windowWidth = pixels * 10;
const int windowHeight = pixels * 22;
const bool debug = true;
const int pixels = 32.0f;
const int rows = 22;
const int columns = 10;

GridController * GridController::s_instance = nullptr;
sf::RenderWindow * GridController::m_windowref = nullptr;

GridController* GridController::instance() {
    static GridController instance;
    std::cout << "instance pointer = " << &instance;
    return &instance;
}

GridController::GridController() {}

GridController::~GridController() {}

bool GridController::isSpaceOccupied(int row, int col) {
    return this->grid[col][row];
}

void GridController::setSpaceOccupied(int row, int col, bool occupied) {
    this->grid[col][row] = occupied;
}

void GridController::printGrid() {
    for (int i = 0; i < columns*rows; i++) {
        std::cout << this->grid[0][i] << " ";
        if (i % 5 == 4) {
            std::cout << std::endl;
        }
    }
}

void GridController::provideWindow(sf::RenderWindow * window) {
    this->m_windowref = window;
}

sf::RenderWindow * GridController::window_instance() {
    return this->m_windowref;
}
