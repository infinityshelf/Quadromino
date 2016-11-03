#ifndef MONOMINO_H
#define MONOMINO_H
#include "TetrisPiece.hpp"
#include "TetrominoTypes.hpp"

class TetrisPiece;

extern const int pixels;

namespace Monomino {
    sf::RectangleShape rectangleShapeForType(TetrominoType type);
    sf::Color colorForType(TetrominoType type);
}

#endif
