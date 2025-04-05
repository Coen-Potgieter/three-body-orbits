

#ifndef PLANET_H
#define PLANET_H


#include <SFML/Graphics.hpp>
#include "constants.h"
#include <iostream>

class Planet {

public:

    sf::CircleShape body;
    float mass;
    sf::Vector2f a;
    sf::Vector2f v;
    float radius;
    sf::Color colour;
    std::vector<sf::Vector2f> trailHistory;
    sf::Color trailCol;

    Planet(sf::Vector2f initialVelocity, sf::Vector2f initialPos, float inpMass, float inpRadius, sf::Color inpCol, sf::Color inpTrailCol);
    ~Planet() = default;



    void move();
    void draw(sf::RenderWindow& target, sf::Shader& shader) const;

    // This is a comparison operator to tell `std::find` how to compare other planets (position and mass together)
    bool operator==(const Planet& other) const {
        return body.getPosition() == other.body.getPosition() && mass == other.mass;
    }
};

#endif
