#include "TetrisPiece.hpp"
#include <iostream>
#include <random>

const bool drawBBox = true;

const uint16_t kGRID_NONE = 0b0000000000000000;
const uint16_t kGRID_O =    0b0000011001100000;
const uint16_t kGRID_I =    0b0000111100000000;
const uint16_t kGRID_L =    0b0000010001000110;
const uint16_t kGRID_J =    0b0000001000100110;
const uint16_t kGRID_S =    0b0000010001100010;
const uint16_t kGRID_Z =    0b0000001001100100;
const uint16_t kGRID_T =    0b0000001001110000;

sf::RenderWindow*   TetrisPiece::m_windowRef =       nullptr;
GridController*     TetrisPiece::m_gridController =  nullptr;
TetrominoType       TetrisPiece::type =              TETROMINO_TYPE_I;
sf::RectangleShape  TetrisPiece::bbox =              sf::RectangleShape();

TetrisPiece::TetrisPiece() : x(0), y(0), col(0), row(0) {
    this->m_gridController = GridController::instance();
    this->m_windowRef = this->m_gridController->window_instance();
}

void TetrisPiece::setType(TetrominoType type) {
    this->type = type;
}

void TetrisPiece::moveLeft() {
    if (this->offsetFree(-1, 0)) {
        this->updatePosition(this->col-1, this->row);
    }
}

void TetrisPiece::moveRight() {
    if (this->offsetFree(1, 0)) {
        this->updatePosition(this->col+1, this->row+0);
    }
}

void TetrisPiece::moveDown() {
    if (this->offsetFree(0, 1)) {
        this->updatePosition(this->col, this->row+1);
    }
}

void TetrisPiece::rotateClockwise() {
    std::cout << "rotateClockwise" << std::endl;
    bool newGrid[4][4];
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            newGrid[x][y] = this->grid[4-1-y][x];
        }
    }
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            this->grid[y][x] = newGrid[y][x];
        }
    }
    this->setShapes();
}

void TetrisPiece::rotateCounterClockwise() {
    std::cout << "rotateClockwise" << std::endl;
    bool newGrid[4][4];
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            newGrid[x][y] = this->grid[y][x];
        }
    }
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            this->grid[y][x] = newGrid[4-1-y][x];
        }
    }
    this->setShapes();
}

bool TetrisPiece::offsetFree(int col_off, int row_off) {
    bool free = true;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            if (this->grid[row][col]) {
                std::cout << "checking " << this->col+col << ", " << this->row+row << std::endl;
                if (this->row+row+1 >= ROWS && row_off) {
                    free = false;
                    this->lock();
                    break;
                }
                if (this->m_gridController->isSpaceOccupied(this->col+col+col_off, this->row+row+row_off)) {
                    free = false;
                    this->lock();
                    break;
                }
            }
        }
    }
    std::cout << ((free) ? "free" : "taken") << std::endl;
    return free;
}

void TetrisPiece::updatePosition(int col, int row) {
    int x = col * pixels, y = row * pixels;
    this->row = row;
    this->col = col;
    int dx = x - this->x, dy = y - this->y;
    this->x = x;
    this->y = y;
    for (int i = 0; i < 4; i++) {
        // xr and yr are rectangle positions
        this->updateRectUsingDelta(dx, dy, this->rectShapes[i]);
    }
    this->updateRectUsingDelta(dx, dy, this->bbox);
}

void TetrisPiece::lock() {
    this->locked = true;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; ++col) {
            // this->printGrid();
            // reminder col is x and row is y
            int global_row = this->row+row;
            int global_col = this->col+col;
            bool occupied = this->grid[row][col];
            if (occupied) {
                std::cout << "here!!! TetrisPiece.cpp:87 TetrisPiece::lock" << std::endl;
                this->m_gridController->setSpaceOccupied(global_col,global_row,this->type);
            }
        }
    }
    this->m_gridController->printGrid();
}

void TetrisPiece::updateRectUsingDelta(int dx, int dy, sf::RectangleShape &shape) {
    int rect_x, rect_y;
    const sf::Vector2<float> pos = shape.getPosition();
    rect_x = pos.x + dx;
    rect_y = pos.y + dy;
    shape.setPosition(rect_x, rect_y);
}

void TetrisPiece::updatePosition() {
    // if this->x or this->y have been changed directly
    // then updatePosition() should recalculate the positions of all the rectangles
    // this->m_gridController->printGrid();
    std::cerr << "update position without arguments" << std::endl;
    this->setShapes();
}

void TetrisPiece::draw() {
    for (int i = 0; i < 4; i++) {
        this->m_windowRef->draw(this->rectShapes[i]);
    }
    if (drawBBox)this->m_windowRef->draw(this->bbox);
}

void TetrisPiece::setShapes() {
    //this->setGridForType(this->type);
    int rect = 0;
    for (int row = 0; row < 4 && rect < 4; row++) {
        for (int col = 0; col < 4 && rect < 4; col++) {
            if (this->grid[row][col]) {
                this->rectShapes[rect] = Monomino::rectangleShapeForType(this->type);
                this->rectShapes[rect].setPosition(this->x+(col*pixels), this->y+(row*pixels));
                rect++;
            }
        }
    }
    this->bbox.setSize(sf::Vector2f(pixels * 4, pixels * 4));
    this->bbox.setPosition(this->x, this->y);
    this->bbox.setFillColor(sf::Color(0xFFFFFF7F));
    this->bbox.setOutlineColor(sf::Color(0xFFFFFFFF));
    this->bbox.setOutlineThickness(3);
    this->printGrid();
}

void TetrisPiece::printGrid() {
    int max = 4*4;
    // std::cout << "TetrisPiece::printGrid() start" << std::endl << "printing grid" << std::endl;
    std::cout << "+----+" << std::endl;
    for (int i = 0; i < max; i++) {
        if (i % 4 == 0) {
            std::cout << '|';
        }
        std::cout << ((this->grid[0][i]) ? '@':' ');
        if (i % 4 == 3) {
            std::cout << '|' << std::endl;
        }
    }
    std::cout << "+----+" << std::endl;
    // std::cout << "TetrisPiece::printGrid() did end" << std::endl;
}

void TetrisPiece::setGrid() {
    uint16_t type;
    // const char type_string[17];
    switch(this->type) {
        case TETROMINO_TYPE_NONE: {
            type = kGRID_NONE;
            break;
        }
        case TETROMINO_TYPE_O: {
            type = kGRID_O;
            break;
        }
        case TETROMINO_TYPE_I: {
            type = kGRID_I;
            break;
        }
        case TETROMINO_TYPE_L: {
            type = kGRID_L;
            break;
        }
        case TETROMINO_TYPE_J: {
            type = kGRID_J;
            // type_string = kGRID_J
            break;
        }
        case TETROMINO_TYPE_S: {
            type = kGRID_S;
            break;
        }
        case TETROMINO_TYPE_Z: {
            type = kGRID_Z;
            break;
        }
        case TETROMINO_TYPE_T: {
            type = kGRID_T;
            break;
        }
        case TETROMINO_TYPE_MAX: {
            type = kGRID_NONE;
            break;
        }
    }
    std::cout << "type: "<< static_cast<int>(this->type) << std::endl;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            grid[y][x] = (type >> (4*y + x)) & 1;
        }
    }
}

void TetrisPiece::reset() {
    this->locked = false;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1,100);
    int intType = dist(mt);
    intType = intType % 7 + 1;
    std::cout << "random: " << intType << std::endl;
    TetrominoType newType = static_cast<TetrominoType>(intType);
    this->setType(newType);
    this->setGrid();
    this->setShapes();
    this->updatePosition(3, 0);
}
