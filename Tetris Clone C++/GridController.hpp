#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H
#include "TetrisPiece.hpp"
#include "TetrominoTypes.hpp"
#define ROWS 20
#define COLUMNS 10
extern const int windowWidth;
extern const int windowHeight;
extern const bool debug;
extern const int pixels;
extern const char fileName[];
extern int level;
class TetrisPiece;

class GridController {
private:
    TetrominoType grid[ROWS][COLUMNS];
    static GridController *s_instance;
    static sf::RenderWindow * m_windowref;
    GridController();
    GridController(GridController const&);
    void operator=(GridController const&);
    void clearRow(int row);
    void checkRows();
    void shiftRowsAbove(int clearedRow);
    static char characterForType(TetrominoType type);
    static TetrominoType typeForCharacter(char place);
    sf::Font scoreFont;
    sf::Text scoreText;
public:
    ~GridController();
    void draw();
    static GridController* instance();
    sf::RenderWindow * window_instance();
    void provideWindow(sf::RenderWindow * window);
    void printGrid();
    void setSpaceOccupied(int row, int col, TetrominoType type);
    bool isSpaceOccupied(int row, int col);
    void saveGridToFile();
    void loadGridFromFile();
};
#endif
