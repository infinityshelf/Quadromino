#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H
#include "TetrisPiece.hpp"
#define ROWS 22
#define COLUMNS 10
extern const int windowWidth;
extern const int windowHeight;
extern const bool debug;
extern const int pixels;
extern const int rows;
extern const int columns;

class TetrisPiece;

// typedef enum TETRONIMO_TYPES TetronimoType;

class GridController {
private:
    // TetrisPiece *pieces;
    TetronimoType grid[ROWS][COLUMNS];
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
    void setSpaceOccupied(int row, int col, TetronimoType type);
    bool isSpaceOccupied(int row, int col);
};
#endif
