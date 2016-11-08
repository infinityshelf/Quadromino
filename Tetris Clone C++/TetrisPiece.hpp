#ifndef TETRISPIECE_H
#define TETRISPIECE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GridController.hpp"
#include "Monomino.hpp"
#include "TetrominoTypes.hpp"
#include <iostream>

class GridController;

class TetrisPiece
{
private:
    bool grid[4][4];
    int gridSize[2];
    static sf::RenderWindow * m_windowRef;
    static GridController * m_gridController;
    void setShapes();
    static TetrominoType type;
    void updateRectUsingDelta(int dx, int dy, sf::RectangleShape &shape);
    bool offsetFree(int colOff, int rowOff);
    bool offsetFree(bool offsetGrid[4][4], int colOff, int rowOff, bool lock);

    bool rotateFree(bool newGrid[4][4], int bounds);
    bool rotateFree(bool newGrid[4][4], int bounds, int colOff, int rowOff);

    void setGrid(bool newGrid[4][4], int bounds, int colOff, int rowOff);
    void setGrid(bool newGrid[4][4], int bounds);
    void setGrid(bool newGrid[4][4]);
public:
    int x, y, col, row;
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
    void rotateClockwise();
    void rotateCounterClockwise();
    void updatePosition(int col, int row);
    void draw();
    void setGridForType(TetrominoType tetrominoType);
    void setGridForType();
    void reset();
    void moveToStartPosition();
};
#endif
