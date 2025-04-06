#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>
#include <SFML/Graphics.hpp>

// Window Config
constexpr uint16_t WINDOW_WIDTH = 1300;
constexpr uint16_t WINDOW_HEIGHT = 800;
constexpr float dt = 0.01f;

constexpr sf::Color STAR_COLOUR = sf::Color(255, 255, 255);

constexpr sf::Color TEAL = sf::Color(20, 255, 236); 
constexpr sf::Color BLUE = sf::Color(80, 160, 255); 
constexpr sf::Color YELLOW = sf::Color(255, 223, 0); 
constexpr sf::Color GREEN = sf::Color(0, 255, 128); 
constexpr sf::Color ORANGE = sf::Color(255, 140, 0); 
constexpr sf::Color SKY_BLUE = sf::Color(0, 191, 255); 
constexpr sf::Color PURPLE = sf::Color(176, 38, 255); 
constexpr sf::Color RED = sf::Color( 255, 87, 51); 

constexpr sf::Color GREEN_TRAIL = sf::Color(144, 238, 144); 
constexpr sf::Color ORANGE_TRAIL = sf::Color(255, 200, 100); 
constexpr sf::Color SKY_BLUE_TRAIL = sf::Color(173, 216, 230); 
constexpr sf::Color BLUE_TRAIL = sf::Color(80, 160, 255); 
constexpr sf::Color YELLOW_TRAIL = sf::Color(255, 223, 0); 
constexpr sf::Color PURPLE_TRAIL = sf::Color(196,147,255); 


constexpr sf::Color P1_COL = GREEN;
constexpr sf::Color P2_COL = ORANGE;
constexpr sf::Color P3_COL = BLUE;

constexpr size_t TRAIL_LENGTH = 1100;
constexpr float TRAIL_SIZE = 2.f;
constexpr sf::Color TRAIL_COL1 = GREEN_TRAIL;
constexpr sf::Color TRAIL_COL2 = ORANGE_TRAIL;
constexpr sf::Color TRAIL_COL3 = BLUE_TRAIL;

constexpr float PI = 3.14159265389793;
constexpr float EPSILON = 0;

#endif
