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

    /* std::unordered_map<std::string, std::any> inpMap = sunEarthMoon(); */
    std::unordered_map<std::string, std::any> inpMap = lagrangeOrbit();
    /* std::unordered_map<std::string, std::any> inpMap = test(); */

    SolarSystem solarSystem = SolarSystem(
        std::any_cast<std::vector<sf::Vector2f>&>(inpMap["vel"]), 
        std::any_cast<std::vector<float>&>(inpMap["mass"]), 
        std::any_cast<std::vector<sf::Vector2f>&>(inpMap["pos"]), 
        std::any_cast<std::vector<float>&>(inpMap["radii"]),
        std::any_cast<std::vector<sf::Color>&>(inpMap["cols"]),
        std::any_cast<std::vector<sf::Color>&>(inpMap["trailCols"]),
        std::any_cast<float&>(inpMap["g"])
    );

    // Init Background
    int numStars = 20;
    float radius = 1.5;
    sf::Color col = STAR_COLOUR;

    Background bg(20, radius, col);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }



        /* sf::Vector2i mousePos = sf::Mouse::getPosition(window); */
        window.clear();
        bg.draw(window);

        solarSystem.draw(window);
        window.display();
    }
}

