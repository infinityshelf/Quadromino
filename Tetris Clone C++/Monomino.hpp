#ifndef MONOMINO_H
#define MONOMINO_H
#include "TetrisPiece.hpp"

extern const int pixels;

class Monomino {
private:
    static sf::RectangleShape pieces[7];
public:
    // should instantiate pieces to be the correct rectangles of the correct color.
    Unomino();
    sf::RectangleShape rectangleShapeForType(TetronimoType);
}

#endif
