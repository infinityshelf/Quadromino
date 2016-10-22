#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef TETRISPIECE_H
#define TETRISPIECE_H
#include "GridController.hpp"
class GridController;

enum TETRONIMO_TYPES
{
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
    GridController &m_gridController;
    int x, y, col, row;
    bool grid[4][4];
    sf::RenderWindow &m_windowRef;
    GridController *nullable_m_gridController;
    sf::Color color;
    void setShapeForType(TetronimoType tetronimoType);
    TetronimoType type;
    void updateRectUsingDelta(int dx, int dy, sf::RectangleShape &shape);
public:
    ~TetrisPiece(){};
    sf::RectangleShape rectShapes[4];
    sf::RectangleShape bbox;
    TetrisPiece(TetrisPiece const&);
    TetrisPiece(GridController &gridController, sf::RenderWindow &windowRef);
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