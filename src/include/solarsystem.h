#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include <stdint.h>
#include <vector>
#include <math.h>
#include "planet.h"
#include "constants.h"
#include <iostream>
#include <stdint.h>

class SolarSystem {

public:

    std::vector<Planet> planets;
    float G;
    sf::Shader glowShader;
    size_t trailLength;

    SolarSystem(std::vector<sf::Vector2f> initialVelocity, std::vector<float> mass, std::vector<sf::Vector2f> initialPos, std::vector<float> inpRadius, std::vector<sf::Color> inpCols, std::vector<sf::Color> inpTrailCols, size_t inpTrailLength, float inpG);
    ~SolarSystem() = default;

    void draw(sf::RenderWindow& target);
    void update();
    void handleCollisions();
};

#endif
