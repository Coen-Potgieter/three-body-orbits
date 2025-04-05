
#include "../include/solarsystem.h"
SolarSystem::SolarSystem(std::vector<sf::Vector2f> initialVelocity, std::vector<float> mass, std::vector<sf::Vector2f> initialPos, std::vector<float> inpRadius, std::vector<sf::Color> inpCols, std::vector<sf::Color> inpTrailCols, float inpG) {


    if (initialVelocity.size() != mass.size() || initialVelocity.size() != initialPos.size()) {
        throw std::invalid_argument("IDK");
    }


    int numPlanets = initialVelocity.size();

    G = inpG;

    for (size_t i = 0; i < numPlanets; i++) {
        planets.push_back(Planet(initialVelocity[i], initialPos[i], mass[i], inpRadius[i], inpCols[i], inpTrailCols[i]));
    }

    if (!glowShader.loadFromFile("../src/assets/shaders/glow.frag", sf::Shader::Type::Fragment)) {
        std::cout << "Failed to Load Shader" << std::endl;
    }
}


sf::Color blendColors(const sf::Color& a, const sf::Color& b, float t) {
    t = std::clamp(t, 0.f, 1.f); // Clamp between 0 and 1
    return sf::Color(
        static_cast<uint8_t>(a.r + t * (b.r - a.r)),
        static_cast<uint8_t>(a.g + t * (b.g - a.g)),
        static_cast<uint8_t>(a.b + t * (b.b - a.b)),
        static_cast<uint8_t>(a.a + t * (b.a - a.a))
    );
}

void SolarSystem::draw(sf::RenderWindow& target) {

    int numPlanets = planets.size();

    // If We have 1 planet then don't move him
    if (numPlanets <= 1) {
        planets[0].draw(target, glowShader);
        return;
    }

    // Track average position of planets for camera correction
    sf::Vector2f avgPos = { 0.f, 0.f };

    // Loop through every planet
    for (size_t currPlanet = 0; currPlanet < numPlanets; currPlanet++) {

        planets[currPlanet].a = { 0.f, 0.f };

        // Get current planet position
        sf::Vector2f currentPos = planets[currPlanet].body.getPosition();

        // Add to average position
        avgPos += currentPos;

        // Get the current planet's mass
        float currMass = planets[currPlanet].mass;

        // Loop through every other planet
        for (size_t otherPlanet = 0; otherPlanet < numPlanets; otherPlanet++) {

            // If we loop through planet in outer loop then continue
            if (currPlanet == otherPlanet) continue;


            // Get position and mass of other planet
            sf::Vector2f otherPos = planets[otherPlanet].body.getPosition();
            float otherMass = planets[otherPlanet].mass;

            // Do math
            sf::Vector2f direction = otherPos - currentPos;
            float distance = std::sqrt(direction.x*direction.x + direction.y*direction.y);

            // If distance is too small then merge the planets
            if (distance <= planets[currPlanet].radius + planets[otherPlanet].radius) {
                // New planet
                sf::Vector2f newV = (currMass*planets[currPlanet].v + otherMass*planets[otherPlanet].v) / (currMass + otherMass);
                sf::Color newCol = blendColors(planets[currPlanet].colour, planets[otherPlanet].colour, 0.5);
                sf::Color newTrailCol = blendColors(planets[currPlanet].trailCol, planets[otherPlanet].trailCol, 0.5);
                planets.push_back(Planet(newV, currentPos, currMass + otherMass, planets[currPlanet].radius + planets[otherPlanet].radius, newCol, newTrailCol));

                // Remove merging planets from vector (Remove last index then first index)
                size_t removal1 = std::max(currPlanet, otherPlanet);
                size_t removal2 = std::min(currPlanet, otherPlanet);

                planets.erase(planets.begin() + removal1);
                planets.erase(planets.begin() + removal2);

                // This may a bad idea (simply move to next frame in the simulation)
                return;
            }

            // Get Force
            float forceMag = (G*otherMass*currMass) / (distance*distance + EPSILON*EPSILON);
            sf::Vector2f force = (direction*forceMag) / distance;

            // Add it to acceleration
            planets[currPlanet].a += force / currMass;
        }

        // Move the planet
        planets[currPlanet].move();

    }

    // calculate camera correction 
    avgPos /= static_cast<float>(numPlanets);
    sf::Vector2f correction = sf::Vector2f(WINDOW_WIDTH/2.0, WINDOW_HEIGHT/2.0) - avgPos;

    // Loop through every planet to correct and draw
    for (size_t currPlanet = 0; currPlanet < numPlanets; currPlanet++) {
        planets[currPlanet].body.move(correction);

        // Draw the planet
        planets[currPlanet].draw(target, glowShader);

    }
}


