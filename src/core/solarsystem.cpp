
#include "../include/solarsystem.h"
SolarSystem::SolarSystem(std::vector<sf::Vector2f> initialVelocity, std::vector<float> mass, std::vector<sf::Vector2f> initialPos, std::vector<float> inpRadius, std::vector<sf::Color> inpCols, std::vector<sf::Color> inpTrailCols, size_t inpTrailLength, float inpG) {


    if (initialVelocity.size() != mass.size() || initialVelocity.size() != initialPos.size()) {
        throw std::invalid_argument("IDK");
    }


    int numPlanets = initialVelocity.size();

    G = inpG;
    trailLength = inpTrailLength;

    for (size_t i = 0; i < numPlanets; i++) {
        planets.push_back(Planet(initialVelocity[i], initialPos[i], mass[i], inpRadius[i], inpCols[i], inpTrailCols[i], trailLength));
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

    // Loop through every planet to correct and draw
    for (auto& planet : planets) {
        // Draw the planet
        planet.draw(target, glowShader);
    }
}

void SolarSystem::update() {
    int numPlanets = planets.size();
    if (numPlanets <= 1) return;

    sf::Vector2f avgPos = { 0.f, 0.f };

    // First calculate all accelerations
    for (size_t i = 0; i < numPlanets; i++) {
        planets[i].a = {0.f, 0.f}; // Reset acceleration
        
        // Add to average position
        avgPos += planets[i].body.getPosition();

        for (size_t j = 0; j < numPlanets; j++) {
            if (i == j) continue;

            sf::Vector2f r = planets[j].body.getPosition() - planets[i].body.getPosition();
            float distSq = r.x * r.x + r.y * r.y;
            float dist = std::sqrt(distSq);

            // Force calculation with proper softening
            float forceMag = G * planets[i].mass * planets[j].mass / (distSq + EPSILON * EPSILON);
            planets[i].a += (r / dist) * (forceMag / planets[i].mass);

        }
    }

    // calculate camera correction 
    avgPos /= static_cast<float>(numPlanets);
    sf::Vector2f correction = sf::Vector2f(WINDOW_WIDTH/2.0, WINDOW_HEIGHT/2.0) - avgPos;

    // Then update positions and velocities
    for (auto& planet : planets) {
        planet.move(correction); 
    }

    // Handle collisions in a separate pass
    handleCollisions();
}

void SolarSystem::handleCollisions() {

    // Loop through every planet
    for (size_t i = 0; i < planets.size(); i++) {

        // Get current planet position
        sf::Vector2f currentPos = planets[i].body.getPosition();

        // Get the current planet's mass
        float currMass = planets[i].mass;

        // Loop through every other planet
        for (size_t j = 0; j < planets.size(); j++) {

            // If we loop through planet in outer loop then continue
            if (i == j) continue;

            // Get position and mass of other planet
            sf::Vector2f otherPos = planets[j].body.getPosition();
            float otherMass = planets[j].mass;

            // Do math
            sf::Vector2f direction = otherPos - currentPos;
            float distance = std::sqrt(direction.x*direction.x + direction.y*direction.y);

            // If distance is too small then merge the planets
            if (distance <= planets[i].radius + planets[j].radius) {
                // New planet
                sf::Vector2f newV = (currMass*planets[i].v + otherMass*planets[j].v) / (currMass + otherMass);
                sf::Color newCol = blendColors(planets[i].colour, planets[j].colour, 0.5);
                sf::Color newTrailCol = blendColors(planets[i].trailCol, planets[j].trailCol, 0.5);
                planets.push_back(Planet(newV, currentPos, currMass + otherMass, planets[i].radius + planets[j].radius, newCol, newTrailCol, trailLength));

                // Remove merging planets from vector (Remove last index then first index)
                size_t removal1 = std::max(i, j);
                size_t removal2 = std::min(i, j);

                planets.erase(planets.begin() + removal1);
                planets.erase(planets.begin() + removal2);

                // This may a bad idea (simply move to next frame in the simulation)
                return;
            }
        }
    }

}
