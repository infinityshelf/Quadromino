#include "TetrisPiece.hpp"
#include "GridController.hpp"
#include <iostream>


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
TetronimoType       TetrisPiece::type =              TETRONIMO_TYPE_I;
sf::RectangleShape  TetrisPiece::bbox =              sf::RectangleShape();
sf::Color           TetrisPiece::color =             sf::Color(0xFFFFFFFF);

TetrisPiece::TetrisPiece() : x(0), y(0), col(0), row(0) {
    this->m_gridController = GridController::instance();
    this->m_windowRef = this->m_gridController->window_instance();
}

void TetrisPiece::setType(TetronimoType type) {
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
                if (this->m_gridController->isSpaceOccupied(this->col+col+col_off, this->row+row+row_off) || this->row+row+1 >= max_rows) {
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

void TetrisPiece::stick() {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; ++col) {
            // this->printGrid();
            // reminder col is x and row is y
            int global_row = this->row+row;
            int global_col = this->col+col;
            bool occupied = this->grid[row][col];
            if (occupied) {
                this->m_gridController->setSpaceOccupied(global_col,global_row,this->type);
            }
        }
    }
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
    this->m_windowRef->draw(this->bbox);
}

void TetrisPiece::setShapeForType(TetronimoType tetronimoType) {
    sf::Vector2f square = sf::Vector2f(pixels, pixels);
    switch(tetronimoType) {
        case TETRONIMO_TYPE_NONE:
            break;
        case TETRONIMO_TYPE_O: {
            this->color = sf::Color(0xFFFF00FF);
            break;
        }
        case TETRONIMO_TYPE_I: {
            this->color = sf::Color(0x00FFFFFF);
            break;
        }
        case TETRONIMO_TYPE_L: {
            this->color = sf::Color(0xFF7F00FF);
            break;
        }
        case TETRONIMO_TYPE_J: {
            this->color = sf::Color(0x0000FFFF);
            break;
        }
        case TETRONIMO_TYPE_S: {
            this->color = sf::Color(0x00FF00FF);
            break;
        }
        case TETRONIMO_TYPE_Z: {
            this->color = sf::Color(0xFF0000FF);
            break;
        }
        case TETRONIMO_TYPE_T: {
            this->color = sf::Color(0x7F00FFFF);
            break;
        }
    }
    this->setGridForType(this->type);
    int rect = 0;
    for (int row = 0; row < 4 && rect < 4; row++) {
        for (int col = 0; col < 4 && rect < 4; col++) {
            if (this->grid[row][col]) {
                rect++;
                this->rectShapes[rect-1].setSize(square);
                this->rectShapes[rect-1].setFillColor(this->color);
                this->rectShapes[rect-1].setPosition(this->x+(col*pixels), this->y+(row*pixels));
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

void TetrisPiece::setGridForType(TetronimoType tetronimoType) {
    uint16_t type;
    // const char type_string[17];
    switch(tetronimoType) {
        case TETRONIMO_TYPE_NONE: {
            type = kGRID_NONE;
            break;
        }
        case TETRONIMO_TYPE_O: {
            type = kGRID_O;
            break;
        }
        case TETRONIMO_TYPE_I: {
            type = kGRID_I;
            break;
        }
        case TETRONIMO_TYPE_L: {
            type = kGRID_L;
            break;
        }
        case TETRONIMO_TYPE_J: {
            type = kGRID_J;
            // type_string = kGRID_J
            break;
        }
        case TETRONIMO_TYPE_S: {
            type = kGRID_S;
            break;
        }
        case TETRONIMO_TYPE_Z: {
            type = kGRID_Z;
            break;
        }
        case TETRONIMO_TYPE_T: {
            type = kGRID_T;
            break;
        }
        default: {
            type = kGRID_NONE;
            break;
        }
    }
    std::cout << "type: "<< static_cast<int>(type) << std::endl;
    int max = (4*4) - 1;
    int i = max;
    int j = 0;
    for (; i > 0 && j < max; i--, j++) {
        grid[0][j] = type >> i & 1;
        // grid[0][j] = (type_string[j] == "_") ? true : false;
        // std::cout << "grid " << i << " = " << (int) grid[0][j] << std::endl;
    }
}

void TetrisPiece::resetWithType(TetronimoType tetronimoType) {
    this->type = tetronimoType;
    this->setShapeForType(tetronimoType);
    this->updatePosition(3, 0);
}

// void TetrisPiece::destroy() {
//     // delete this->bbox;
//     for (int i = 0; i < 4; i++) {
//         // delete this->rectShapes[i];
//     }
// }
