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
    static sf::RenderWindow * m_windowRef;
    static GridController * m_gridController;
    void setShapes();
    static TetrominoType type;
    void updateRectUsingDelta(int dx, int dy, sf::RectangleShape &shape);
    bool offsetFree(int col_off, int row_off);
public:
    int x, y, col, row;
    sf::RectangleShape rectShapes[4];
    static sf::RectangleShape bbox;
    TetrisPiece();
    void lock();
    void setType(TetrominoType type);
    void moveLeft();
    void moveRight();
    void moveDown();
    void updatePosition(int col, int row);
    void updatePosition();
    void draw();
    void printGrid();
    void setGridForType(TetrominoType TETROMINOType);
    void resetWithType(TetrominoType TETROMINOType);
};
#endif
