#ifndef UNOMINO_H
#define UNOMINO_H
#include "TetrisPiece.hpp"

extern const int pixels;

class Unomino {
private:
    static sf::RectangleShape pieces[7];
public:
    // should instantiate pieces to be the correct rectangles of the correct color.
    Unomino();
    sf::RectangleShape rectangleShapeForType(TetronimoType);
}

#endif
