#include <SFML/Graphics.hpp>

#include "./include/constants.h"
#include "./include/solarsystem.h"
#include "./include/initialconditions.h"
#include "./include/background.h"


int main()
{
    // For smooth edges on shapes
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "My Window", sf::Style::Default, sf::State::Windowed, settings);

    // Fixes visual tearing casued by out of sync window with screen
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // ------------------------ Various Orbits ---------------------- //
    /* std::unordered_map<std::string, std::any> inpMap = lagrangeOrbit(); */
    /* std::unordered_map<std::string, std::any> inpMap = eulerOrbit(); */
    /* std::unordered_map<std::string, std::any> inpMap = figure8Orbit(); */
    /* std::unordered_map<std::string, std::any> inpMap = BroukeA3(); */
    std::unordered_map<std::string, std::any> inpMap = BroukeA7();

    // Setting up simulation with given initial conditions
    SolarSystem solarSystem = SolarSystem(
        std::any_cast<std::vector<sf::Vector2f>&>(inpMap["vel"]), 
        std::any_cast<std::vector<float>&>(inpMap["mass"]), 
        std::any_cast<std::vector<sf::Vector2f>&>(inpMap["pos"]), 
        std::any_cast<std::vector<float>&>(inpMap["radii"]),
        std::any_cast<std::vector<sf::Color>&>(inpMap["cols"]),
        std::any_cast<std::vector<sf::Color>&>(inpMap["trailCols"]),
        std::any_cast<size_t&>(inpMap["trailLength"]),
        std::any_cast<float&>(inpMap["g"])
    );

    // Init Background
    int numStars = 20;
    float radius = 1.5;
    sf::Color col = STAR_COLOUR;
    Background bg(20, radius, col);

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        static float accumulator = 0.0f;
        float frameTime = clock.restart().asSeconds();
        // Limit frame time to prevent spiral of death
        if (frameTime > 0.25f)
            frameTime = 0.25f;

        accumulator += frameTime;

        // Update physics with fixed time step
        while (accumulator >= dt) {
            solarSystem.update(); 
            accumulator -= dt;
        }

        window.clear();
        bg.draw(window);

        solarSystem.draw(window);
        window.display();
    }
}

