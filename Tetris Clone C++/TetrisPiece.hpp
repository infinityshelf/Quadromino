#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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

extern const float pixels;

class TetrisPiece
{
private:
    int x, y;
    uint16_t grid;
    sf::RenderWindow &m_windowRef;
    sf::Color color;
    void setShapeForType();
    TetronimoType type;
public:
    sf::RectangleShape rectShapes[4];
    TetrisPiece(sf::RenderWindow &windowRef): m_windowRef(windowRef){};
    void setType(TetronimoType type);
    void moveLeft();
    void moveRight();
    void moveDown();
    void updatePosition(int x, int y);
    void updatePosition();
    void draw();
};
