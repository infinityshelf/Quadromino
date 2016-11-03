/*
* @Author: gilletthernandez
* @Date:   2016-10-27 01:25:45
* @File name: Unomino.cpp
* @Last Modified by:   gilletthernandez
* @Last Modified time: 2016-10-27 01:33:12
*/

#include <iostream>
#include "Monomino.hpp"

using namespace std;

sf::RectangleShape Monomino::rectangleShapeForType(TetrominoType type) {
    sf::RectangleShape shape;
    sf::Vector2f square = sf::Vector2f(pixels, pixels);
    shape.setSize(square);
    shape.setFillColor(Monomino::colorForType(type));
    return shape;
}

sf::Color Monomino::colorForType (TetrominoType type) {
    switch(type) {
        case TETROMINO_TYPE_O: {
            return sf::Color(0xFFFF00FF);
        }
        case TETROMINO_TYPE_I: {
            return sf::Color(0x00FFFFFF);
        }
        case TETROMINO_TYPE_L: {
            return sf::Color(0xFF7F00FF);
        }
        case TETROMINO_TYPE_J: {
            return sf::Color(0x0000FFFF);
        }
        case TETROMINO_TYPE_S: {
            return sf::Color(0x00FF00FF);
        }
        case TETROMINO_TYPE_Z: {
            return sf::Color(0xFF0000FF);
        }
        case TETROMINO_TYPE_T: {
            return sf::Color(0x7F00FFFF);
        }
        case TETROMINO_TYPE_MAX:{
            return sf::Color(0xFFFF0000);
        };
        case TETROMINO_TYPE_NONE: {
            return sf::Color(0xE0B0FF66);
        }
        default: {
            return sf::Color(0x00000000);
        }
    }
}
