#include <iostream>
#include <fstream>
#include "drawing.h"
using namespace std;

// SCUFFED this draws a circle but registers it as a square - close enough 
void drawing(sf::RenderWindow& window, vector<sf::CircleShape>& shapes, vector<bool>& pixels, int radius, sf::Color color, bool state) {
    sf::CircleShape shape(radius);
    shape.setFillColor(color);
    shape.setPosition(sf::Mouse::getPosition(window).x-shape.getRadius(), sf::Mouse::getPosition(window).y-shape.getRadius()); // draw at center of mouse
    shapes.push_back(shape);

    // update pixels when drawn
    for (int x = shape.getPosition().x; x < shape.getPosition().x + 2 * shape.getRadius(); ++x) {
        for (int y = shape.getPosition().y; y < shape.getPosition().y + 2 * shape.getRadius(); ++y) {
            if (x >= 0 && x < 800 && y >= 0 && y < 600) {
                pixels[y * 800 + x] = state;
            }
        }
    }
}

void getData(vector<bool>& pixels) {
    ofstream programPixles("pixels.txt");
    ofstream userPixels("pixels_nice.txt");
    if (programPixles.is_open() && userPixels.is_open()) {
        for (int y = 0; y < 600; y++) {
            for (int x = 0; x < 800; x++) {
                if (pixels[y * 800 + x]) {
                    programPixles << "1 "; // write 1 for white pixel
                    userPixels << "1 ";
                } else {
                    programPixles << "0 "; // write 0 for black pixel
                    userPixels << "0 ";
                }
            }
            userPixels << '\n';
        }
        cout << "pixel state saved to pixels.txt and pixels_nice.txt\n";
    } else {
        cout << "unable to open pixels.txt and/or pixels_nice.txt\n";
    }
}

void erase(vector<bool>& pixels, vector<sf::CircleShape>& shapes) {
    shapes.clear();
    pixels.assign(800*600, false);
    cout << "input erased\n";
}