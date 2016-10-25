#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H
#include "TetrisPiece.hpp"
extern const int windowWidth;
extern const int windowHeight;
extern const bool debug;
extern const int pixels;
extern const int max_rows;
extern const int max_columns;
class TetrisPiece;
class GridController
{
private:
    TetrisPiece *pieces;
    bool grid[10][22];
    static GridController *s_instance;
    static sf::RenderWindow * m_windowref;
    GridController();
    GridController(GridController const&);
    void operator=(GridController const&);
public:
    ~GridController();
    static GridController* instance();
    sf::RenderWindow * window_instance();
    void provideWindow(sf::RenderWindow * window);
    void printGrid();
    void setSpaceOccupied(int row, int col, bool occupied);
    bool isSpaceOccupied(int row, int col);
};
#endif
