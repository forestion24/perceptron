#ifndef DRAWING_H
#define DRAWING_H

#include <SFML/Graphics.hpp>
#include <vector>

void drawing(sf::RenderWindow& window, std::vector<sf::CircleShape>& shapes, std::vector<bool>& pixels, int radius, sf::Color color, bool state);
void getData(std::vector<bool>& pixels);
void erase(std::vector<bool>& pixels, std::vector<sf::CircleShape>& shapes);

#endif