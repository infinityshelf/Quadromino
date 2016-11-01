#include "TetrisPiece.hpp"
#include <iostream>
#include <string.h>
#include <random>

const bool drawBBox = false;


const char kGRID_NONE[17] =     "____"
                                "____"
                                "____"
                                "____";

const char kGRID_O[17] =        "_@@_"
                                "_@@_"
                                "____"
                                "y___";

const char kGRID_I[17] =        "____"
                                "@@@@"
                                "____"
                                "____";

const char kGRID_L[17] =        "__@x"
                                "@@@_"
                                "____"
                                "y___";

const char kGRID_J[17] =        "@__x"
                                "@@@_"
                                "____"
                                "y___";

const char kGRID_S[17] =        "_@@x"
                                "@@__"
                                "____"
                                "y___";

const char kGRID_Z[17] =        "@@_x"
                                "_@@_"
                                "____"
                                "y___";

const char kGRID_T[17] =        "_@_x"
                                "@@@_"
                                "____"
                                "y___";

sf::RenderWindow*   TetrisPiece::m_windowRef =       nullptr;
GridController*     TetrisPiece::m_gridController =  nullptr;
TetrominoType       TetrisPiece::type =              TETROMINO_TYPE_I;
sf::RectangleShape  TetrisPiece::bbox =              sf::RectangleShape();

TetrisPiece::TetrisPiece() : x(0), y(0), col(0), row(0) {
    this->gridSize[0] = 4;
    this->gridSize[1] = 4;
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
    if (this->type != TETROMINO_TYPE_O) {
        std::cout << "x " << this->gridSize[0] << "y " << this->gridSize[1] << std::endl;
        int bounds = 0;
        int x = this->gridSize[0];
        int y = this->gridSize[1];
        if (x == y) {
            bounds = x&y;
        }
        std::cout << "rotateClockwise" << std::endl;
        bool newGrid[4][4];
        for (int y = 0; y < bounds; y++) {
            for (int x = 0; x < bounds; x++) {
                newGrid[x][y] = this->grid[bounds-1-y][x];
            }
        }
        for (int y = 0; y < bounds; y++) {
            for (int x = 0; x < bounds; x++) {
                this->grid[y][x] = newGrid[y][x];
            }
        }
        this->setShapes();
    }
}

void TetrisPiece::rotateCounterClockwise() {
        if (this->type != TETROMINO_TYPE_O) {
        std::cout << "x " << this->gridSize[0] << "y " << this->gridSize[1] << std::endl;
        int bounds = 0;
        int x = this->gridSize[0];
        int y = this->gridSize[1];
        if (x == y) {
            bounds = x&y;
        }
        std::cout << "rotateCounterClockwise" << std::endl;
        bool newGrid[4][4];
        for (int y = 0; y < bounds; y++) {
            for (int x = 0; x < bounds; x++) {
                newGrid[x][y] = this->grid[y][x];
            }
        }
        for (int y = 0; y < bounds; y++) {
            for (int x = 0; x < bounds; x++) {
                this->grid[y][x] = newGrid[bounds-1-y][x];
            }
        }
        this->setShapes();
    }
}

bool TetrisPiece::offsetFree(int col_off, int row_off) {
    bool free = true;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            if (this->grid[row][col]) {
                std::cout << "checking " << this->col+col << ", " << this->row+row << std::endl;
                // this check is for when the piece is hitting the bottom of the grid without encountering a piece
                if (this->row+row+1 >= ROWS && row_off > 0) {
                    free = false;
                    this->lock();
                    break;
                }
                // this check is for attempting to move left or right
                if (this->m_gridController->isSpaceOccupied(this->col+col+col_off, this->row+row)) {
                    free = false;
                    break;
                }
                // this check is for attempting to move down into a space occupied by another space
                if (this->m_gridController->isSpaceOccupied(this->col+col, this->row+row+row_off)) {
                    free = false;
                    this->lock();
                    break;
                }
            }
        }
        if (!free) {
            break;
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

void TetrisPiece::moveToStartPosition() {
    int centerx = static_cast <int> (std::ceil(this->gridSize[0] / 2.0f));
    int centery = static_cast <int> (std::ceil(this->gridSize[1] / 2.0f));
    std::cout << "centery: " << centery << std::endl;
    std::cout << "centerx: " << centerx << std::endl;
    this->updatePosition((COLUMNS / 2) -centerx, 0-2-centery);
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
    this->bbox.setSize(sf::Vector2f(this->gridSize[0] * pixels, this->gridSize[1] * pixels));
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
    char type[17];
    switch(this->type) {
        case TETROMINO_TYPE_O: {
            strcpy(type, kGRID_O);
            break;
        }
        case TETROMINO_TYPE_I: {
            strcpy(type,kGRID_I);
            break;
        }
        case TETROMINO_TYPE_L: {
            strcpy(type,kGRID_L);
            break;
        }
        case TETROMINO_TYPE_J: {
            strcpy(type,kGRID_J);
            break;
        }
        case TETROMINO_TYPE_S: {
            strcpy(type,kGRID_S);
            break;
        }
        case TETROMINO_TYPE_Z: {
            strcpy(type,kGRID_Z);
            break;
        }
        case TETROMINO_TYPE_T: {
            strcpy(type,kGRID_T);
            break;
        }
        case TETROMINO_TYPE_MAX: {}
        case TETROMINO_TYPE_NONE: {}
        default: {
            strcpy(type,kGRID_NONE);
            break;
        }
    }
    std::cout << "type: "<< type << std::endl;
    this->gridSize[0] = 4;
    this->gridSize[1] = 4;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            char gridChar = type[4*y + x];
            grid[y][x] = (gridChar == '@');
            if (y == 0 && gridChar == 'x') {
                this->gridSize[0] = x;
            }
            if (x == 0 && gridChar == 'y') {
                this->gridSize[1] = y;
            }
        }
    }
    std::cout << "this->gridSize[" << this->gridSize[0] << "][" << this->gridSize[1] << "]" << std::endl;
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
    this->moveToStartPosition();
}
