#ifndef TETRIS_TETRISPIECE_H
#define TETRIS_TETRISPIECE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GridController.hpp"
#include "Grids.hpp"
#include "Monomino.hpp"
#include "TetrominoTypes.hpp"
#include <iostream>

class GridController;

class TetrisPiece {
private:
    bool grid[4][4];
    int gridSize[2];
    static GridController * m_gridController;
    void setShapes();
    static TetrominoType type;
    bool offsetFree(int colOff, int rowOff);
    bool offsetFree(bool offsetGrid[4][4], int colOff, int rowOff);

    bool rotateFree(bool newGrid[4][4], int bounds);
    bool rotateFree(bool newGrid[4][4], int bounds, int colOff, int rowOff);

    void setGrid(bool newGrid[4][4]);
    void setGrid(bool newGrid[4][4], int bounds);
    void setGrid(bool newGrid[4][4], int bounds, int colOff, int rowOff);
public:
    // x, y are pixel-based positions
    int x, y;
    // col, row are grid-based positions
    int col, row;
    unsigned int frameCounter;
    sf::RectangleShape rectShapes[4];
    static sf::RectangleShape bbox;
    TetrisPiece();
    void lock();
    bool locked;
    void setType(TetrominoType type);
    TetrominoType getType();
    void moveLeft();
    void moveRight();
    void moveDown();
    bool rotateClockwise();
    bool rotateCounterClockwise();
    void updatePosition(int col, int row);
    void drawToWindow(sf::RenderWindow &window);
    void setGridForType(TetrominoType tetrominoType);
    void setGridForType();
    int castDown(bool for_real);
    void reset();
    void moveToStartPosition();
};
#endif
