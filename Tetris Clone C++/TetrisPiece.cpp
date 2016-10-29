#include "TetrisPiece.hpp"
#include <iostream>

const bool drawBBox = false;

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
sf::Color           TetrisPiece::color =             sf::Color(0xFFFFFFFF);

TetrisPiece::TetrisPiece() : x(0), y(0), col(0), row(0) {
    this->m_gridController = GridController::instance();
    this->m_windowRef = this->m_gridController->window_instance();
}

void TetrisPiece::setType(TetrominoType type) {
    this->type = type;
    this->setShapeForType(this->type);
}

void TetrisPiece::moveLeft() {
    this->updatePosition(this->col-1, this->row);
}

void TetrisPiece::moveRight() {
    this->updatePosition(this->col+1, this->row);
}

void TetrisPiece::moveDown() {
    bool canMoveDown = true;
    canMoveDown = this->offsetFree(0, 1);
    // std::cout << "canMoveDown: " << canMoveDown << std::endl;
    if (canMoveDown) {
        this->updatePosition(this->col, this->row+1);
    }
}

bool TetrisPiece::offsetFree(int col_off, int row_off) {
    bool free = true;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            if (this->grid[row][col]) {
                std::cout << "checking " << this->col+col << ", " << this->row+row << std::endl;
                if (this->m_gridController->isSpaceOccupied(this->col+col+col_off, this->row+row+row_off) || this->row+row+1 >= ROWS) {
                    free = false;
                    break;
                }
            }
        }
    }
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
    this->setShapeForType(this->type);
}

void TetrisPiece::draw() {
    for (int i = 0; i < 4; i++) {
        this->m_windowRef->draw(this->rectShapes[i]);
    }
    if (drawBBox)this->m_windowRef->draw(this->bbox);
}

void TetrisPiece::setShapeForType(TetrominoType type) {
    this->setGridForType(this->type);
    int rect = 0;
    for (int row = 0; row < 4 && rect < 4; row++) {
        for (int col = 0; col < 4 && rect < 4; col++) {
            if (this->grid[row][col]) {
                this->rectShapes[rect] = Monomino::rectangleShapeForType(type);
                this->rectShapes[rect].setPosition(this->x+(col*pixels), this->y+(row*pixels));
                rect++;
            }
        }
    }
    this->bbox.setSize(sf::Vector2f(pixels * 4, pixels * 4));
    this->bbox.setPosition(this->x, this->y);
    this->bbox.setFillColor(sf::Color(0xFFFFFF00));
    this->bbox.setOutlineColor(sf::Color(0xFFFFFFFF));
    this->bbox.setOutlineThickness(1);
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

void TetrisPiece::setGridForType(TetrominoType tetrominoType) {
    uint16_t type;
    // const char type_string[17];
    switch(tetrominoType) {
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
        default: {
            type = kGRID_NONE;
            break;
        }
    }
    std::cout << "type: "<< static_cast<int>(type) << std::endl;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            grid[y][x] = (type >> (4*y + x)) & 1;
        }
    }
}

void TetrisPiece::resetWithType(TetrominoType type) {
    this->type = type;
    this->setShapeForType(type);
    this->updatePosition(3, 0);
}

// void TetrisPiece::destroy() {
//     // delete this->bbox;
//     for (int i = 0; i < 4; i++) {
//         // delete this->rectShapes[i];
//     }
// }
