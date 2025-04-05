
#include "../include/initialconditions.h"

std::unordered_map<std::string, std::any> lagrangeOrbit() {

    /* float g = 38.5; */
    /* float g = 40.f; */
    /* float g = 38.2; */
    /* float g = 50.5; */

    float planetMass = 100.f;
    float planetRaduis = 10.f;
    float posY = WINDOW_HEIGHT / 2.0;
    float posX = WINDOW_WIDTH / 2.0;
    float offset = 250.f;

    sf::Vector2f p1 = { posX, posY - offset };
    sf::Vector2f p2 = { posX - offset * std::cos(30 * PI/180), posY + offset * std::sin(30 * PI/180) };
    sf::Vector2f p3 = { posX + offset * std::cos(30 * PI/180), posY + offset * std::sin(30 * PI/180) };

    sf::Color p1Col = P1_COL;
    sf::Color p2Col = P2_COL;
    sf::Color p3Col = P3_COL;

    sf::Color p1Trail = TRAIL_COL1;
    sf::Color p2Trail = TRAIL_COL2;
    sf::Color p3Trail = TRAIL_COL3;

    // Calculate the required orbital velocity
    // For an equilateral triangle with sides of length L, each body is at distance L from the others
    float L = offset * std::sqrt(3); // Side length of the triangle

    // Calculate gravitational constant based on the required orbital period
    // For a rotating triangular system, the orbital period T must satisfy: T² = (4π²L³)/(3GM)
    // Rearranging for G: G = (4π²L³)/(3MT²)

    // Let's set the angular velocity ω for the system
    float angularVelocity = 0.02; // Adjust this for desired rotation speed

    // This gives us T = 2π/ω
    float period = 2 * PI / angularVelocity;

    // Calculate required G for this period
    float g = (4 * PI * PI * L * L * L) / (3 * planetMass * period * period);

    // Calculate the tangential velocity based on angular velocity
    float v = angularVelocity * offset;
    /* // Velocities */
    /* float v = 3; */

    std::vector<sf::Vector2f> initialVelocity = {
        sf::Vector2f( -1, 0 ) * v,
        sf::Vector2f( std::cos(60 * PI/180), std::sin(60 * PI/180) ) * v,
        sf::Vector2f( std::sin(30 * PI/180), -std::cos(30 * PI/180) ) * v,
    };

    // Initialise Vectors
    std::vector<sf::Vector2f> initialPos = { p1, p2, p3 };
    std::vector<float> masses = { planetMass, planetMass, planetMass };
    std::vector<float> radii = { planetRaduis, planetRaduis, planetRaduis };
    std::vector<sf::Color> cols = { p1Col, p2Col, p3Col };
    std::vector<sf::Color> trailCols = { p1Trail, p2Trail, p3Trail };

    std::unordered_map<std::string, std::any> map;

    map["pos"] = initialPos;
    map["vel"] = initialVelocity;
    map["mass"] = masses;
    map["radii"] = radii;
    map["cols"] = cols;
    map["trailCols"] = trailCols;
    map["g"] = g;
    return map;

}

std::unordered_map<std::string, std::any> test() {

    /* float g = 38.5; */
    /* float g = 40.f; */
    float g = 200;
    /* float g = 50.5; */

    float planetMass = 100.f;
    float planetRaduis = 10.f;
    float posY = WINDOW_HEIGHT / 2.0;
    float posX = WINDOW_WIDTH / 2.0;
    float offset = 250.f;

    sf::Vector2f p1 = { posX, posY - offset };
    sf::Vector2f p2 = { posX, posY + offset };

    sf::Color p1Col = P1_COL;
    sf::Color p2Col = P2_COL;

    sf::Color p1Trail = TRAIL_COL1;
    sf::Color p2Trail = TRAIL_COL2;

    // Velocities
    float v = 3;

    std::vector<sf::Vector2f> initialVelocity = {
        sf::Vector2f( -2, 0 ) * v,
        sf::Vector2f( 1, 0 ) * v,
    };

    // Initialise Vectors
    std::vector<sf::Vector2f> initialPos = { p1, p2 };
    std::vector<float> masses = { planetMass, planetMass };
    std::vector<float> radii = { planetRaduis, planetRaduis };
    std::vector<sf::Color> cols = { p1Col, p2Col };
    std::vector<sf::Color> trailCols = { p1Trail, p2Trail };

    std::unordered_map<std::string, std::any> map;

    map["pos"] = initialPos;
    map["vel"] = initialVelocity;
    map["mass"] = masses;
    map["radii"] = radii;
    map["cols"] = cols;
    map["trailCols"] = trailCols;
    map["g"] = g;
    return map;

}

