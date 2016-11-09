#include "TetrisPiece.hpp"
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

TetrisPiece::TetrisPiece() : x(0), y(0), col(0), row(0), locked(false) {
    this->gridSize[0] = 4;
    this->gridSize[1] = 4;
    this->m_gridController = GridController::instance();
    this->m_windowRef = this->m_gridController->window_instance();
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
        this->updatePosition(this->col+1, this->row+0);
    }
}

void TetrisPiece::moveDown() {
    if (this->offsetFree(0, 1)) {
        this->updatePosition(this->col, this->row+1);
    }
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
                    || colOff+x < 0
                    || colOff+x >= COLUMNS
                    || rowOff+y < 0
                    || rowOff+y >= ROWS) {
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

bool TetrisPiece::rotateClockwise() {
    bool rotated = false;
    if (debug) std::cout << "clockwise" << std::endl;
    if (this->type != TETROMINO_TYPE_O) {

        int bounds = 0;
        int width = this->gridSize[0];
        int height = this->gridSize[1];
        if (width == height) {
            bounds = width;
        } else {
            return rotated;
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
            rotated = true;
        } else if (this->rotateFree(transposedGrid, bounds, this->col-1, this->row)) {
            this->setGrid(transposedGrid, bounds, this->col-1, this->row);
            rotated = true;
        } else if (this->rotateFree(transposedGrid, bounds, this->col-1, this->row-1)) {
            this->setGrid(transposedGrid, bounds, this->col-1, this->row-1);
            rotated = true;
        } else if (this->rotateFree(transposedGrid, bounds, this->col+1, this->row)) {
            this->setGrid(transposedGrid, bounds, this->col+1, this->row);
            rotated = true;
        } else if (this->rotateFree(transposedGrid, bounds, this->col+1, this->row-1)) {
            this->setGrid(transposedGrid, bounds, this->col+1, this->row-1);
            rotated = true;
        } else if (this->rotateFree(transposedGrid, bounds, this->col, this->row-1)) {
            this->setGrid(transposedGrid, bounds, this->col, this->row-1);
            rotated = true;
        }
    }
    return rotated;
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

bool TetrisPiece::rotateCounterClockwise() {
    bool rotated = false;
    if (this->type != TETROMINO_TYPE_O) {

        int bounds = 0;
        int width = this->gridSize[0];
        int height = this->gridSize[1];
        if (width == height) {
            bounds = width;
        } else {
            return rotated;
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
            rotated = true;
        } else if (this->rotateFree(rotatedGrid, bounds, this->col-1, this->row)) {
            this->setGrid(rotatedGrid, bounds, this->col-1, this->row);
            rotated = true;
        } else if (this->rotateFree(rotatedGrid, bounds, this->col-1, this->row-1)) {
            this->setGrid(rotatedGrid, bounds, this->col-1, this->row-1);
            rotated = true;
        } else if (this->rotateFree(rotatedGrid, bounds, this->col+1, this->row)) {
            this->setGrid(rotatedGrid, bounds, this->col+1, this->row);
            rotated = true;
        } else if (this->rotateFree(rotatedGrid, bounds, this->col+1, this->row-1)) {
            this->setGrid(rotatedGrid, bounds, this->col+1, this->row-1);
            rotated = true;
        } else if (this->rotateFree(rotatedGrid, bounds, this->col, this->row-1)) {
            this->setGrid(rotatedGrid, bounds, this->col, this->row-1);
            rotated = true;
        }
    }
    return rotated;
}

bool TetrisPiece::offsetFree(bool offsetGrid[4][4], int colOff, int rowOff, bool lock) {
    bool free = true;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            if (offsetGrid[row][col]) {
        
                // if going past bottom row
                if (this->row+row+1 >= ROWS && rowOff > 0) {
                    free = false;
                    if (lock) this->lock();
                    break;
                }
                // if moving out of the grid left or right
                if (this->col+col+colOff < 0 || this->col+col+colOff >= COLUMNS) {
                    free = false;
                    break;
                }
                // these 2 may be able to be consolidated
                //if the row is occupied
                if (this->m_gridController->isSpaceOccupied(this->col+col+colOff, this->row+row)) {
                    free = false;
                    break;
                }
                //if the col is occupied
                if (this->m_gridController->isSpaceOccupied(this->col+col, this->row+row+rowOff)) {
                    free = false;
                    if (lock) this->lock();
                    break;
                }
            }
        }
        if (!free) {
            break;
        }
    }
    return free;
}

bool TetrisPiece::offsetFree(int colOff, int rowOff) {
    return this->offsetFree(this->grid, colOff, rowOff, true);
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

void TetrisPiece::updateRectUsingDelta(int dx, int dy, sf::RectangleShape &shape) {
    int rect_x, rect_y;
    const sf::Vector2<float> pos = shape.getPosition();
    rect_x = (int) pos.x + dx;
    rect_y = (int) pos.y + dy;
    shape.setPosition(rect_x, rect_y);
}

void TetrisPiece::draw() {
    for (int i = 0; i < 4; i++) {
        this->m_windowRef->draw(this->rectShapes[i]);
    }
    if (drawBBox) this->m_windowRef->draw(this->bbox);
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
            if (y == 0 && gridChar == 'x') {
                this->gridSize[0] = x;
            }
            if (x == 0 && gridChar == 'y') {
                this->gridSize[1] = y;
            }
        }
    }
}

void TetrisPiece::reset() {
    this->locked = false;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1,100);
    int intType = (int) dist(mt);
    intType = intType % 7 + 1;
    TetrominoType newType = static_cast<TetrominoType>(intType);
    this->setType(newType);
    this->setGridForType(newType);
    this->setShapes();
    this->moveToStartPosition();
}
