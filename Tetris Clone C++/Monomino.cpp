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

//sf::RectangleShape *Monomino::pieces = nullptr;

Monomino::Monomino() {
    /*do stuff here*/;
    int max = TETROMINO_TYPE_MAX;
    for (int i = 0; i < max; i++) {
        switch(i) {
            case TETROMINO_TYPE_O: {
                std::cout << "before: " << &this->pieces[TETROMINO_TYPE_O];
                this->pieces[i] = Monomino::rectangleShapeForType(TETROMINO_TYPE_O);
               std::cout << "after: " << &this->pieces[TETROMINO_TYPE_O];
                break;
            }
            case TETROMINO_TYPE_I: {
                break;
            }
            case TETROMINO_TYPE_L: {
                break;
            }
            case TETROMINO_TYPE_J: {
                break;
            }
            case TETROMINO_TYPE_S: {
                break;
            }
            case TETROMINO_TYPE_Z: {
                break;
            }
            case TETROMINO_TYPE_T: {
                break;
            }
            case TETROMINO_TYPE_MAX:{};
            case TETROMINO_TYPE_NONE: {
                break;
            }
        }
    }
}

Monomino::~Monomino() {

}

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
    }
}
