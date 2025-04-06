
#include "../include/initialconditions.h"

std::unordered_map<std::string, std::any> lagrangeOrbit() {

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
    float angularVelocity = 0.01; // Adjust this for desired rotation speed

    // This gives us T = 2π/ω
    float period = 2 * PI / angularVelocity;

    // Calculate required G for this period
    float g = (4 * PI * PI * L * L * L) / (3 * planetMass * period * period);

    // Calculate the tangential velocity based on angular velocity
    float v = angularVelocity * offset;

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
    size_t trailLength = 200;

    std::unordered_map<std::string, std::any> map;

    map["pos"] = initialPos;
    map["vel"] = initialVelocity;
    map["mass"] = masses;
    map["radii"] = radii;
    map["cols"] = cols;
    map["trailCols"] = trailCols;
    map["g"] = g;
    map["trailLength"] = trailLength;

    // Print the calculated values for reference
    std::cout << "Configured Lagrange orbit with:" << std::endl;
    std::cout << "  Angular velocity: " << angularVelocity << std::endl;
    std::cout << "  G value: " << g << std::endl;

    return map;

}

std::unordered_map<std::string, std::any> eulerOrbit() {
    // Configuration parameters
    float centerMass = 100.f;       // Mass of the central body
    float outerMass = centerMass * 0.5f; // Mass of the two outer bodies (smaller)

    float planetRadius = 10.f;      // Base radius for visualization
    float centerRadius = planetRadius * std::cbrt(centerMass/outerMass) * 2; // Scale radius by cube root of mass
    float outerRadius = planetRadius;

    float posY = WINDOW_HEIGHT / 2.0;
    float posX = WINDOW_WIDTH / 2.0;

    // Euler's three-body problem uses a specific distance ratio
    // The two smaller masses are positioned at approximately ±3.67 times the distance from center
    float eulerRatio = 3.6742346141747673f; // Precise value for equal masses ratio
    float centerOffset = 100.f;  // Distance from center to the first outer body

    // Position setup for collinear configuration (along X-axis)
    sf::Vector2f p1 = { posX - eulerRatio * centerOffset, posY }; // Left body
    sf::Vector2f p2 = { posX, posY };                             // Center body
    sf::Vector2f p3 = { posX + eulerRatio * centerOffset, posY }; // Right body

    // Colors
    sf::Color p1Col = P1_COL;
    sf::Color p2Col = P2_COL;
    sf::Color p3Col = P3_COL;
    sf::Color p1Trail = TRAIL_COL1;
    sf::Color p2Trail = TRAIL_COL2;
    sf::Color p3Trail = TRAIL_COL3;

    // For the Euler problem, all bodies rotate around their common center of mass
    // The correct angular velocity depends on the gravitational constant G
    float g = 40.0f; // You may need to adjust this

    // Calculate the required orbital speed based on the Euler configuration
    // The system rotates as a rigid body, so angular velocity is the same for all bodies
    float angularVelocity = std::sqrt(g * centerMass / (std::pow(eulerRatio * centerOffset, 3))) * 1.055;

    // Calculate linear velocities perpendicular to position vectors (for rigid body rotation)
    std::vector<sf::Vector2f> initialVelocity = {
        sf::Vector2f(0, angularVelocity * eulerRatio * centerOffset),   // Left body moves up
        sf::Vector2f(0, 0),                                             // Center body stationary
        sf::Vector2f(0, -angularVelocity * eulerRatio * centerOffset)   // Right body moves down
    };

    // Initialise vectors
    std::vector<sf::Vector2f> initialPos = { p1, p2, p3 };
    std::vector<float> masses = { outerMass, centerMass, outerMass };
    std::vector<float> radii = { outerRadius, centerRadius, outerRadius };
    std::vector<sf::Color> cols = { p1Col, p2Col, p3Col };
    std::vector<sf::Color> trailCols = { p1Trail, p2Trail, p3Trail };
    size_t trailLength = 200;

    std::unordered_map<std::string, std::any> map;
    map["pos"] = initialPos;
    map["vel"] = initialVelocity;
    map["mass"] = masses;
    map["radii"] = radii;
    map["cols"] = cols;
    map["trailCols"] = trailCols;
    map["g"] = g;
    map["trailLength"] = trailLength;

    // Print the calculated values for reference
    std::cout << "Configured Euler orbit with:" << std::endl;
    std::cout << "Euler ratio: " << eulerRatio << std::endl;
    std::cout << "Angular velocity: " << angularVelocity << std::endl;
    std::cout << "G value: " << g << std::endl;

    return map;
}

std::unordered_map<std::string, std::any> figure8Orbit() {
    float mass = 100.f;
    float radius = 10.f;
    float g = 16.0f; // You might still need to tweak G slightly for stability

    // Window center
    float posY = WINDOW_HEIGHT / 2.0;
    float posX = WINDOW_WIDTH / 2.0;

    // Position and velocity values for a figure-8 orbit (symmetric and periodic)
    std::vector<sf::Vector2f> initialPos = {
        sf::Vector2f(-0.97000436f,  0.24308753f),
        sf::Vector2f( 0.97000436f, -0.24308753f),
        sf::Vector2f(0.f, 0.f)
    };

    std::vector<sf::Vector2f> initialVelocity = {
        sf::Vector2f(0.4662036850f, 0.4323657300f),
        sf::Vector2f(0.4662036850f, 0.4323657300f),
        sf::Vector2f(-0.93240737f, -0.86473146f)
    };

    // Scale and center
    float scale = 400.0f;
    for (auto& pos : initialPos) {
        pos = pos * scale + sf::Vector2f(posX, posY);
    }

    float velocityScale = 2.f;
    for (auto& vel : initialVelocity) {
        vel *= velocityScale;
    }

    std::vector<float> masses = { mass, mass, mass };
    std::vector<float> radii = { radius, radius, radius };

    std::vector<sf::Color> cols = { P1_COL, P2_COL, P3_COL };
    std::vector<sf::Color> trailCols = { TRAIL_COL1, TRAIL_COL2, TRAIL_COL3 };
    size_t trailLength = 400;

    std::unordered_map<std::string, std::any> map;
    map["pos"] = initialPos;
    map["vel"] = initialVelocity;
    map["mass"] = masses;
    map["radii"] = radii;
    map["cols"] = cols;
    map["trailCols"] = trailCols;
    map["g"] = g;
    map["trailLength"] = trailLength;

    std::cout << "Configured figure-8 orbit" << std::endl;

    return map;
}

std::unordered_map<std::string, std::any> BroukeA3() {

    float mass = 100.f;
    float radius = 10.f;
    float g = 10.f; 

    float posY = WINDOW_HEIGHT / 2.0f;
    float posX = WINDOW_WIDTH / 2.0f;

    float posScale = 250.f;

    std::vector<sf::Vector2f> initialPos = {
        { posX + 0.812382071f * posScale, posY},
        { posX - 1.1273158206f * posScale, posY},
        { posX + 0.3149337497f * posScale, posY},
    };

    float vScale = 2;

    std::vector<sf::Vector2f> initialVelocity = {
        sf::Vector2f(0.f, 1.4601869417f) * vScale,
        sf::Vector2f(0.f, -0.8973577042f) * vScale,
        sf::Vector2f(0.f, -0.5628292375f) * vScale,
    };

    std::vector<float> masses = { mass, mass, mass };
    std::vector<float> radii = { radius, radius, radius };


    std::vector<sf::Color> cols = { P1_COL, P2_COL, P3_COL };
    std::vector<sf::Color> trailCols = { TRAIL_COL1, TRAIL_COL2, TRAIL_COL3 };
    size_t trailLength = 1100;


    std::unordered_map<std::string, std::any> map;
    map["pos"] = initialPos;
    map["vel"] = initialVelocity;
    map["mass"] = masses;
    map["radii"] = radii;
    map["cols"] = cols;
    map["trailCols"] = trailCols;
    map["g"] = g;
    map["trailLength"] = trailLength;

    std::cout << "BrouckeA3 Orbit Initialized!" << std::endl;

    return map;
}


std::unordered_map<std::string, std::any> BroukeA7() {
    float mass = 100.f;
    float radius = 10.f;
    float g = 18.f; 

    float posY = WINDOW_HEIGHT / 2.0f;
    float posX = WINDOW_WIDTH / 2.0f;

    float posScale = 200.f;

    std::vector<sf::Vector2f> initialPos = {
        { posX - 0.1095519101f * posScale, posY},
        { posX + 1.6613533905f * posScale, posY},
        { posX - 1.5518014804f * posScale, posY},
    };


    float vScale = 3;

    std::vector<sf::Vector2f> initialVelocity = {
        sf::Vector2f(0, 0.9913358338) * vScale,
        sf::Vector2f(0, -0.1569959746) * vScale,
        sf::Vector2f(0, -0.8343398592) * vScale,
    };


    std::vector<float> masses = { mass, mass, mass };
    std::vector<float> radii = { radius, radius, radius };


    std::vector<sf::Color> cols = { P1_COL, P2_COL, P3_COL };
    std::vector<sf::Color> trailCols = { TRAIL_COL1, TRAIL_COL2, TRAIL_COL3 };
    size_t trailLength = 1100;


    std::unordered_map<std::string, std::any> map;
    map["pos"] = initialPos;
    map["vel"] = initialVelocity;
    map["mass"] = masses;
    map["radii"] = radii;
    map["cols"] = cols;
    map["trailCols"] = trailCols;
    map["g"] = g;
    map["trailLength"] = trailLength;

    std::cout << "Computed G = " << g << std::endl;
    std::cout << "BrouckeA3 Orbit Initialized!" << std::endl;

    return map;
}

