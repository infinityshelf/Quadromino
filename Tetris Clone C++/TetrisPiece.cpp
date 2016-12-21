#include "TetrisPiece.hpp"
#include <random>
#include <cassert>
#include <cstring>

class bad_arguments: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Function called with bad arguments";
  }
} bad_arg;

const bool drawBBox = false;

GridController*     TetrisPiece::m_gridController =  nullptr;
TetrominoType       TetrisPiece::type =              TETROMINO_TYPE_I;
sf::RectangleShape  TetrisPiece::bbox =              sf::RectangleShape();

TetrisPiece::TetrisPiece() : x(0), y(0), col(0), row(0), locked(false) {
    this->gridSize[0] = 4;
    this->gridSize[1] = 4;
    this->m_gridController = GridController::instance();
}

void TetrisPiece::setType(TetrominoType type) {
    this->type = type;
}

TetrominoType TetrisPiece::getType() {
    return this->type;
}

void TetrisPiece::moveLeft() {
    if (this->offsetFree(-1, 0)) {
        this->updatePosition(this->col-1, this->row);
    }
}

void TetrisPiece::moveRight() {
    if (this->offsetFree(1, 0)) {
        this->updatePosition(this->col+1, this->row);
    }
}

void TetrisPiece::moveDown() {
    if (this->offsetFree(0, 1)) {
        this->updatePosition(this->col, this->row+1);
    } else {
        this->lock();
    }
}

int TetrisPiece::castDown(bool for_real) {
    int index = 0;
    // lookahead to avoid needing to do `index--`
    while (this->offsetFree(0, index+1)) {
        index++;
    }
    if (for_real) {
        this->updatePosition(this->col, this->row + index);
    }
    return index;
}

bool TetrisPiece::rotateFree(bool newGrid[4][4], int bounds) {
    return this->rotateFree(newGrid, bounds, this->col, this->row);
}
bool TetrisPiece::rotateFree(bool newGrid[4][4], int bounds, int colOff, int rowOff) {
    bool rotateFree = true;
    for (int y = 0; y < bounds; y++) {
        if (rotateFree == false) {
            break;
        }
        for (int x = 0; x < bounds; x++) {
            if (newGrid[y][x] == true) {
                if (this->m_gridController->isSpaceOccupied(colOff+x, rowOff+y)
                    or colOff+x < 0
                    or colOff+x >= COLUMNS
                    //or rowOff+y < 0
                    or rowOff+y >= ROWS) {
                    rotateFree = false;
                    break;
                }
            }
        }
    }
    if (debug) std::cout << "rotate " << ((rotateFree) ? "free" : "not free") << std::endl;
    return rotateFree;
}
void TetrisPiece::setGrid(bool newGrid[4][4], int bounds, int colOff, int rowOff) {
    this->setGrid(newGrid, bounds);
    this->setShapes();
    this->updatePosition(colOff, rowOff);
}

void TetrisPiece::setGrid(bool newGrid[4][4]) {
    this->setGrid(newGrid, 4);
}
void TetrisPiece::setGrid(bool newGrid[4][4], int bounds) {
    for (int x = 0; x < bounds; x++) {
        for (int y = 0; y < bounds; y++) {
            this->grid[y][x] = newGrid[y][x];
        }
    }
}

bool TetrisPiece::rotateClockwise() {
    bool rotated = true;
    if (debug) std::cout << "clockwise" << std::endl;
    if (this->type != TETROMINO_TYPE_O) {
        int bounds = 0;
        int width = this->gridSize[0];
        int height = this->gridSize[1];
        if (width == height) {
            bounds = width;
        } else {
            throw bad_arg;
        }
        bool rotatedGrid[4][4];
        bool transposedGrid[4][4];

        for (int y = 0; y < bounds; y++) {
            for (int x = 0; x < bounds; x++) {
                rotatedGrid[x][y] = this->grid[bounds-1-y][x];
            }
        }
        for (int y = 0; y < bounds; y++) {
            for (int x = 0; x < bounds; x++) {
                transposedGrid[y][x] = rotatedGrid[y][x];
            }
        }
        if (this->rotateFree(transposedGrid, bounds, this->col, this->row)) {
            this->setGrid(transposedGrid, bounds, this->col, this->row);
        }
        else if (this->rotateFree(transposedGrid, bounds, this->col-1, this->row)) {
            this->setGrid(transposedGrid, bounds, this->col-1, this->row);
            this->frameCounter = 0;
        }
        else if (this->rotateFree(transposedGrid, bounds, this->col-1, this->row-1)) {
            this->setGrid(transposedGrid, bounds, this->col-1, this->row-1);
            this->frameCounter = 0;
        }
        else if (this->rotateFree(transposedGrid, bounds, this->col+1, this->row)) {
            this->setGrid(transposedGrid, bounds, this->col+1, this->row);
            this->frameCounter = 0;
        }
        else if (this->rotateFree(transposedGrid, bounds, this->col+1, this->row-1)) {
            this->setGrid(transposedGrid, bounds, this->col+1, this->row-1);
            this->frameCounter = 0;
        }
        else if (this->rotateFree(transposedGrid, bounds, this->col, this->row-1)) {
            this->setGrid(transposedGrid, bounds, this->col, this->row-1);
            this->frameCounter = 0;
        } else {
            rotated = false;
        }
    } else {
        rotated = false;
    }
    return rotated;
}

bool TetrisPiece::rotateCounterClockwise() {
    bool rotated = true;
    if (debug) std::cout << "counterclockwise" << std::endl;
    if (this->type != TETROMINO_TYPE_O) {
        int bounds = 0;
        int width = this->gridSize[0];
        int height = this->gridSize[1];
        if (width == height) {
            bounds = width;
        } else {
            throw bad_arg;
        }
        bool rotatedGrid[4][4];
        bool transposedGrid[4][4];

        for (int y = 0; y < bounds; y++) {
            for (int x = 0; x < bounds; x++) {
                transposedGrid[x][y] = this->grid[y][x];
            }
        }
        for (int y = 0; y < bounds; y++) {
            for (int x = 0; x < bounds; x++) {
                rotatedGrid[y][x] = transposedGrid[bounds-1-y][x];
            }
        }
        if (this->rotateFree(rotatedGrid, bounds, this->col, this->row)) {
            this->setGrid(rotatedGrid, bounds, this->col, this->row);
        }
        else if (this->rotateFree(rotatedGrid, bounds, this->col-1, this->row)) {
            this->setGrid(rotatedGrid, bounds, this->col-1, this->row);
            this->frameCounter = 0;
        }
        else if (this->rotateFree(rotatedGrid, bounds, this->col-1, this->row-1)) {
            this->setGrid(rotatedGrid, bounds, this->col-1, this->row-1);
            this->frameCounter = 0;
        }
        else if (this->rotateFree(rotatedGrid, bounds, this->col+1, this->row)) {
            this->setGrid(rotatedGrid, bounds, this->col+1, this->row);
            this->frameCounter = 0;
        }
        else if (this->rotateFree(rotatedGrid, bounds, this->col+1, this->row-1)) {
            this->setGrid(rotatedGrid, bounds, this->col+1, this->row-1);
            this->frameCounter = 0;
        }
        else if (this->rotateFree(rotatedGrid, bounds, this->col, this->row-1)) {
            this->setGrid(rotatedGrid, bounds, this->col, this->row-1);
            this->frameCounter = 0;
        } else {
            rotated = false;
        }
    } else {
        rotated = false;
    }
    return rotated;
}

bool TetrisPiece::offsetFree(bool offsetGrid[4][4], int colOff, int rowOff) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (offsetGrid[row][col]) {
                // if going past bottom row
                if (this->row+row+rowOff >= ROWS) {
                    return false;
                }
                // if moving out of the grid left or right
                if (this->col+col+colOff < 0 or this->col+col+colOff >= COLUMNS) {
                    return false;
                }
                // these 2 may be able to be consolidated
                //if the row is occupied
                if (this->m_gridController->isSpaceOccupied(this->col+col+colOff, this->row+row+rowOff)) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool TetrisPiece::offsetFree(int colOff, int rowOff) {
    return this->offsetFree(this->grid, colOff, rowOff);
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
        this->rectShapes[i].move(dx, dy);
    }
    this->bbox.move(dx, dy);
}

void TetrisPiece::moveToStartPosition() {
    int centerx = static_cast <int> (std::ceil(this->gridSize[0] / 2.0f));
    int centery = static_cast <int> (std::ceil(this->gridSize[1] / 2.0f));
    this->updatePosition((COLUMNS / 2) -centerx, 0-2-centery);
}

void TetrisPiece::lock() {
    this->locked = true;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; ++col) {
            // reminder col is x and row is y
            int global_row = this->row+row;
            int global_col = this->col+col;
            bool occupied = this->grid[row][col];
            if (occupied) {

                this->m_gridController->setSpaceOccupied(global_col,global_row,this->type);
            }
        }
    }
    //this->m_gridController->printGrid();
}

void TetrisPiece::drawToWindow(sf::RenderWindow &window) {
    int how_far = this->castDown(false);
    // std::cout << "cast down says how far = " << how_far << std::endl;
    for (int i = 0; i < 4; i++) {
        window.draw(this->rectShapes[i]);
        sf::RectangleShape copy = this->rectShapes[i];
        // auto pos = copy.getPosition();
        copy.move(0, pixels*how_far);
        copy.setFillColor(sf::Color(0x8f8f8f8f));
        //copy.setOutlineColor(sf::Color(0x7F7F7FFF));
        copy.setOutlineThickness(0);
        window.draw(copy);
    }
    if (drawBBox) window.draw(this->bbox);
}

void TetrisPiece::setShapes() {
    //this->setGridForType(this->type);
    int rect = 0;
    for (int row = 0; row < 4 and rect < 4; row++) {
        for (int col = 0; col < 4 and rect < 4; col++) {
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
    this->bbox.setOutlineThickness(3);
}

void TetrisPiece::setGridForType() {
    this->setGridForType(this->type);
}

void TetrisPiece::setGridForType(TetrominoType tetrominoType) {
    char type[17];
    switch(tetrominoType) {
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
    this->gridSize[0] = 4;
    this->gridSize[1] = 4;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            char gridChar = type[4*y + x];
            grid[y][x] = (gridChar == '@');
            if (y == 0 and gridChar == 'x') {
                this->gridSize[0] = x;
            }
            if (x == 0 and gridChar == 'y') {
                this->gridSize[1] = y;
            }
        }
    }
}

void TetrisPiece::resetWithType(TetrominoType type) {
    this->setType(type);
    this->setGridForType(type);
    this->setShapes();
    this->moveToStartPosition();
    this->locked = false;
}

void TetrisPiece::reset() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1,100);
    int intType = (int) dist(mt);
    intType = intType % 7 + 1;
    this->resetWithType(static_cast<TetrominoType>(intType));
}
