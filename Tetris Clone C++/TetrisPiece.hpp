#ifndef TETRISPIECE_H
#define TETRISPIECE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GridController.hpp"

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
    int x, y, col, row;
    bool grid[4][4];
    sf::RenderWindow &m_windowRef;
    sf::Color color;
    void setShapeForType(TetronimoType tetronimoType);
    TetronimoType type;
    void updateRectUsingDelta(int dx, int dy, sf::RectangleShape &shape);
public:
    sf::RectangleShape rectShapes[4];
    sf::RectangleShape bbox;
    TetrisPiece(sf::RenderWindow &windowRef): m_windowRef(windowRef){};
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