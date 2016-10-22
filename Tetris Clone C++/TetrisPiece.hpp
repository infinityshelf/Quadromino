#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef TETRISPIECE_H
#define TETRISPIECE_H
#include "GridController.hpp"

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

class TetrisPiece
{
private:
    bool grid[4][4];
    static sf::RenderWindow * m_windowRef;
    static GridController * m_gridController;
    sf::Color color;
    void setShapeForType(TetronimoType tetronimoType);
    TetronimoType type;
    void updateRectUsingDelta(int dx, int dy, sf::RectangleShape &shape);
    bool offsetFree(int col_off, int row_off);
public:
    int x, y, col, row;
    sf::RectangleShape rectShapes[4];
    sf::RectangleShape bbox;
    TetrisPiece();
    void stick();
    void setType(TetronimoType type);
    void moveLeft();
    void moveRight();
    void moveDown();
    void updatePosition(int col, int row);
    void updatePosition();
    void draw();
    void printGrid();
    void setGridForType(TetronimoType tetronimoType);
};
#endif
