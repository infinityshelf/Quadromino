#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "TetrisPiece.hpp"
#include <iostream>

const float pixels = 32.0f;
const bool wrap = true;

const uint16_t kGRID_O = 0b0000011001100000;
const uint16_t kGRID_I = 0b0000111100000000;
const uint16_t kGRID_L = 0b0000010001000110;
const uint16_t kGRID_J = 0b0000001000100110;
const uint16_t kGRID_S = 0b0000010001100010;
const uint16_t kGRID_Z = 0b0000001001100100;
const uint16_t kGRID_T = 0b0000001001110000;

void TetrisPiece::setType(TetronimoType type) {
    this->type = type;
    this->setShapeForType();
}

void TetrisPiece::moveLeft() {
    this->x -= pixels;
}

void TetrisPiece::moveRight() {
    this->x += pixels;
}

void TetrisPiece::moveDown() {
    this->y += pixels;
}

void TetrisPiece::updatePosition(int x, int y) {
    this->x = x;
    this->y = y;
    if (wrap) {
        //this->y = this->y % windowHeight;
    }
    this->setShapeForType();
}

void TetrisPiece::updatePosition() {
    this->setShapeForType();
}

void TetrisPiece::draw() {
    for (int i = 0; i < 4; i++) {
        this->m_windowRef.draw(this->rectShapes[i]);
    }
}

void TetrisPiece::setShapeForType() {
    sf::Vector2f square = sf::Vector2f(pixels, pixels);
    switch(this->type) {
        case TETRONIMO_TYPE_O: {
            this->grid = kGRID_O;
            this->color = sf::Color(0xFF0000FF);
            this->rectShapes[0].setPosition(this->x, this->y);
            this->rectShapes[1].setPosition(this->x, this->y+pixels);
            this->rectShapes[2].setPosition(this->x+pixels, this->y);
            this->rectShapes[3].setPosition(this->x+pixels, this->y+pixels);
        }
        break;
        case TETRONIMO_TYPE_I: {
            this->grid = kGRID_I;
            this->color = sf::Color(0xFFFF00FF);
            this->rectShapes[0].setPosition(this->x, this->y);
            this->rectShapes[1].setPosition(this->x, this->y+pixels);
            this->rectShapes[2].setPosition(this->x, this->y+(pixels*2));
            this->rectShapes[3].setPosition(this->x, this->y+(pixels*3));
        }
        break;
        case TETRONIMO_TYPE_L: {
            this->grid = kGRID_L;
            this->color = sf::Color(0xFF0000FF);
            this->rectShapes[0].setPosition(this->x, this->y);
            this->rectShapes[1].setPosition(this->x, this->y+pixels);
            this->rectShapes[2].setPosition(this->x, this->y+(pixels*2));
            this->rectShapes[3].setPosition(this->x+pixels, this->y+(pixels*2));
        }
        break;
        case TETRONIMO_TYPE_J: {
            this->grid = kGRID_J;
            this->color = sf::Color(0x0000FFFF);
            this->rectShapes[0].setPosition(this->x+pixels, this->y);
            this->rectShapes[1].setPosition(this->x+pixels, this->y+pixels);
            this->rectShapes[2].setPosition(this->x+pixels, this->y+(pixels*2));
            this->rectShapes[3].setPosition(this->x, this->y+(pixels*2));
        }
        break;
        case TETRONIMO_TYPE_S: {
            this->grid = kGRID_S;
            this->color = sf::Color(0x00FFFFFF);
            this->rectShapes[0].setPosition(this->x, this->y);
            this->rectShapes[1].setPosition(this->x-pixels, this->y);
            this->rectShapes[2].setPosition(this->x-pixels, this->y-pixels);
            this->rectShapes[3].setPosition(this->x, this->y+pixels);
        }
        break;
        case TETRONIMO_TYPE_Z: {
            this->grid = kGRID_Z;
            this->color = sf::Color(0xFF00FFFF);
            this->rectShapes[0].setPosition(this->x, this->y);
            this->rectShapes[1].setPosition(this->x+pixels, this->y);
            this->rectShapes[2].setPosition(this->x+pixels, this->y-pixels);
            this->rectShapes[3].setPosition(this->x, this->y+pixels);
        }
        break;
        case TETRONIMO_TYPE_T: {
            this->grid = kGRID_T;
            this->color = sf::Color(0xFFFFFFFF);
            this->rectShapes[0].setPosition(this->x, this->y);
            this->rectShapes[1].setPosition(this->x+pixels, this->y);
            this->rectShapes[2].setPosition(this->x-pixels, this->y);
            this->rectShapes[3].setPosition(this->x, this->y-pixels);
        }
        break;
    }
    for (int i = 0; i < 4; i++) {
        this->rectShapes[i].setSize(square);
        this->rectShapes[i].setFillColor(this->color);
    }
}