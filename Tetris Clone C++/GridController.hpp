#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H
#include "TetrisPiece.hpp"
extern const int windowWidth;
extern const int windowHeight;
extern const bool debug;
extern const int pixels;
extern const int rows;
extern const int columns;
class TetrisPiece;
class GridController
{
private:
    TetrisPiece *pieces;
    bool grid[10][22];
    static GridController *s_instance;
    GridController();
    GridController(GridController const&);
    void operator=(GridController const&);
public:
    ~GridController();
    static GridController& instance(); 
    void printGrid();
    void setSpaceOccupied(int row, int col, bool occupied);
    bool isSpaceOccupied(int row, int col);
};
#endif