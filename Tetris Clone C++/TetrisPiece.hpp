#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef TETRISPIECE_H
#define TETRISPIECE_H

class GridController;

enum TETRONIMO_TYPES
{
    TETRONIMO_TYPE_NONE,
    TETRONIMO_TYPE_O,
    TETRONIMO_TYPE_T,
    TETRONIMO_TYPE_I,
    TETRONIMO_TYPE_L,
    TETRONIMO_TYPE_J,
    TETRONIMO_TYPE_Z,
    TETRONIMO_TYPE_S
};
typedef enum TETRONIMO_TYPES TetronimoType;

#include "GridController.hpp"

class TetrisPiece
{
private:
    bool grid[4][4];
    int gridSize[2];
    static sf::RenderWindow * m_windowRef;
    static GridController * m_gridController;
    void setShapeForType(TetronimoType tetronimoType);
    static TetronimoType type;
    void updateRectUsingDelta(int dx, int dy, sf::RectangleShape &shape);
    bool offsetFree(int col_off, int row_off);
public:
    int x, y, col, row;
    sf::RectangleShape rectShapes[4];
    static sf::RectangleShape bbox;
    static sf::Color color;
    TetrisPiece();
    void lock();
    void setType(TetronimoType type);
    void moveLeft();
    void moveRight();
    void moveDown();
    void updatePosition(int col, int row);
    void updatePosition();
    void draw();
    void printGrid();
    void setGridForType(TetronimoType tetronimoType);
    void resetWithType(TetronimoType tetronimoType);
};
#endif
