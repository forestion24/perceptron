#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>
#include <fstream>
#include <iostream>
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
    cout << "input erased";
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Digit Recognition");

    vector<sf::CircleShape> shapes;
    vector<bool> pixels(800*600, false);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // check if backspace key is pressed to reset everything
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            erase(pixels, shapes);
        }

        // check if enter key is pressed to save pixel state to file
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            getData(pixels);
        }

        // draw under mouse
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            drawing(window, shapes, pixels, 5, sf::Color::White, true);
        }

        // erase under mouse
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            drawing(window, shapes, pixels, 10, sf::Color::Black, false);
        }
        
        window.clear(sf::Color::Black);

        for (const auto& shape : shapes) {
            window.draw(shape);
        }

        window.display();
    }

    // write pixel state to pixels for the program to use later as input
    ofstream programPixles("pixels.txt");
    if (programPixles.is_open()) {
        for (int y = 0; y < 600; y++) {
            for (int x = 0; x < 800; x++) {
                if (pixels[y * 800 + x]) {
                    programPixles << "1 "; // write 1 for white pixel
                } else {
                    programPixles << "0 "; // write 0 for black pixel
                }
            }
        }
        programPixles.close();
        cout << "pixel state saved to pixles.txt\n";
    } else {
        cout << "unable to open pixels.txt\n";
    }

    // write pixel state to pixels_nice for debugging purposes
    ofstream userPixels("pixels_nice.txt");
    if (userPixels.is_open()) {
        for (int y = 0; y < 600; y++) {
            for (int x = 0; x < 800; x++) {
                if (pixels[y * 800 + x]) {
                    userPixels << "1 "; // write 1 for white pixel
                } else {
                    userPixels << "0 "; // write 0 for black pixel
                }
            }
            userPixels << "\n";
        }
        userPixels.close();
        cout << "pixel state saved to pixles_nice.txt\n";
    } else {
        cout << "unable to open pixels_nice.txt\n";
    }

    return 0;
}


// g++ -o draw.cpp-out draw.cpp -lsfml-graphics -lsfml-window -lsfml-system