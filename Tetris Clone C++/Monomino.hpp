#ifndef MONOMINO_H
#define MONOMINO_H
#include "TetrisPiece.hpp"
#include "TetrominoTypes.hpp"

class TetrisPiece;

extern const int pixels;

class Monomino {
private:
    static sf::RectangleShape pieces[7];
public:
    // should instantiate pieces to be the correct rectangles of the correct color.
    Monomino();
    ~Monomino();
    static sf::RectangleShape rectangleShapeForType(TetrominoType type);
    static sf::Color colorForType(TetrominoType type);
};

#endif
