#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include "drawing.h"
#include "perceptron.h"
using namespace std;


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Alfred");

    vector<sf::CircleShape> shapes;
    vector<bool> pixels(800*600, false);

    while (window.isOpen()) {
        window.setKeyRepeatEnabled(false);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // check if backspace key is pressed to reset everything
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::BackSpace) {
            erase(pixels, shapes);
        }

        // check if enter key is pressed to save pixel state to file
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {
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
        
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
            getData(pixels);

            double learningRate = 0.1;
            Perceptron perceptron("weights.txt", learningRate);

            vector<int> input;
            int label;

            ifstream programPixles("pixels.txt");
            string tmp;
            if (getline(programPixles, tmp)) { // maybe get rid of if statement
                istringstream iss(tmp);
                int x;
                while (iss >> x) {
                    input.push_back(x);
                }
                programPixles.close();
            }

            int guess = perceptron.feedForward(input);
            if (guess == 1) {
                cout << "Alfred thinks circle\n";
            } else if (guess == -1) {
                cout << "Alfred thinks rectangle\n";
            }

            string answer;
            cout << "what did you draw? [r,rectangle,c,circle]\n";
            cin >> answer;
            if (answer == "r" || answer == "rectangle") {
                label = -1;
            } else if (answer == "c" || answer == "circle") {
                label = 1;
            } else {
                cout << "you can't type\n";
            }

            system("./alignWeights.sh");

            perceptron.train(input, label);
            erase(pixels, shapes);
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