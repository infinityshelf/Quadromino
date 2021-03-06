#ifndef TETRIS_MONOMINO_H
#define TETRIS_MONOMINO_H
#include "TetrisPiece.hpp"
#include "TetrominoTypes.hpp"
#include <SFML/Graphics.hpp>

class TetrisPiece;

extern const int pixels;

namespace Monomino {
    sf::RectangleShape rectangleShapeForType(TetrominoType type);
    sf::Color colorForType(TetrominoType type);
}

#endif
