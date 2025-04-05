

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <stdint.h>
#include <SFML/Graphics.hpp>

// Window Config
constexpr uint16_t WINDOW_WIDTH = 1300;
constexpr uint16_t WINDOW_HEIGHT = 800;




constexpr sf::Color STAR_COLOUR = sf::Color(255, 255, 255);
/* constexpr sf::Color P1_COL = sf::Color(255, 0, 0); */
/* constexpr sf::Color P2_COL = sf::Color(255, 255, 0); */
/* constexpr sf::Color P3_COL = sf::Color(0, 255, 0); */

constexpr sf::Color P1_COL = sf::Color(255, 140, 0); // Orange
constexpr sf::Color P2_COL = sf::Color(0, 191, 255); // Deep Sky Blue
/* constexpr sf::Color P3_COL = sf::Color(186, 85, 211); // Purple */
constexpr sf::Color P3_COL = sf::Color(0, 255, 128); // Green

constexpr size_t TRAIL_LENGTH = 300;
constexpr float TRAIL_SIZE = 2.f;
constexpr sf::Color TRAIL_COL1 = sf::Color(255, 200, 100); // Orange
constexpr sf::Color TRAIL_COL2 = sf::Color(173, 216, 230); // Sky Blue
/* constexpr sf::Color TRAIL_COL3 = sf::Color(230, 200, 250); // Purple */
constexpr sf::Color TRAIL_COL3 = sf::Color(144, 238, 144); // Green

constexpr float PI = 3.14159265389793;
constexpr float EPSILON = 0;

#endif
