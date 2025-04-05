

#include "../include/background.h"

Background::Background(int numStars, float size, sf::Color col) {

    for (size_t i = 0; i < numStars; i++) {
        sf::CircleShape star = sf::CircleShape(size);
        star.setFillColor(col);

        // Position
        sf::Vector2f starPos = { static_cast<float>(std::rand() % WINDOW_WIDTH), static_cast<float>(std::rand() % WINDOW_HEIGHT)};
        star.setPosition(starPos);
        stars.push_back(star);
    }


}

void Background::draw(sf::RenderWindow& target) const {
    for (const sf::CircleShape& star : stars) {
        target.draw(star);
    }
}
