

#ifndef BACKGROUND_H
#define BACKGROUND_H


#include <SFML/Graphics.hpp>
#include "constants.h"
#include <vector>

class Background {

public:

    std::vector<sf::CircleShape> stars;


    Background(int numStars, float size, sf::Color col);
    ~Background() = default;


    void draw(sf::RenderWindow& target) const;


};


#endif
