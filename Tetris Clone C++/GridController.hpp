#ifndef TETRIS_GRIDCONTROLLER_H
#define TETRIS_GRIDCONTROLLER_H
#include "TetrisPiece.hpp"
#include "TetrominoTypes.hpp"
const int ROWS = 20;
const int COLUMNS = 10;
extern const int windowWidth;
extern const int windowHeight;
extern const bool debug;
extern const int pixels;
extern const char fileName[];
extern int level;
extern int totalLinesCleared;
extern int score;
extern int level;
extern bool last_clear_was_a_tetris;
class TetrisPiece;

class GridController {
private:
    static GridController *s_instance;
    GridController();
    GridController(GridController const&);
    void operator=(GridController const&);
    void clearRow(int row);
    void shiftRowsAbove(int clearedRow);
    sf::Font scoreFont;
    sf::Text scoreText;
    sf::Sprite bannerSprite;
    sf::Texture bannerTexture;
public:
    static TetrominoType typeForCharacter(char place);
    static char characterForType(TetrominoType type);
    TetrominoType grid[ROWS][COLUMNS];
    void checkRows();
    ~GridController();
    void drawToWindow(sf::RenderWindow &window);
    static GridController* instance();
    sf::RenderWindow * window_instance();
    void printGrid();
    void setSpaceOccupied(int row, int col, TetrominoType type);
    bool isSpaceOccupied(int row, int col);
    TetrominoType typeAtSpace(int row, int col);
};
#endif
