// tetris.cpp
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "TetrisPiece.hpp"

using namespace std;
using namespace sf;

const int windowWidth = pixels * 10;
const int windowHeight = pixels * 20;
const bool debug = false;

int main()
{
    /* code */
    cout << "size of uint8_t" << sizeof(uint8_t) << endl;
    int frameCounter = 0;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Tetris");
    window.setFramerateLimit(60);
    TetrisPiece piece(window);
    piece.updatePosition(pixels*2,0);
    piece.setType(TETRONIMO_TYPE_S);
    while (window.isOpen()) {
        frameCounter++;
        (debug) ? cout << "frame: \n" << frameCounter : NULL;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                (debug) ? cout << "Left\n" : NULL;
                piece.moveLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                (debug) ? cout << "Right\n" : NULL;
                piece.moveRight();
            }
        }
        window.clear();
        if (frameCounter % 60 == 0) {
            frameCounter %= 60;
            piece.moveDown();
        }
        // piece.updatePosition();
        piece.draw();
        window.display();
    }

    return EXIT_SUCCESS;
}
