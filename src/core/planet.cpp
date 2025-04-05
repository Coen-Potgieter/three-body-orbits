

#include "../include/planet.h"



Planet::Planet(sf::Vector2f initialVelocity, sf::Vector2f initialPos, float inpMass, float inpRadius, sf::Color inpCol, sf::Color inpTrailCol) {

    radius = inpRadius;

    body = sf::CircleShape(inpRadius);
    body.setPosition(initialPos);
    body.setOrigin({ radius, radius });

    v = initialVelocity;
    mass = inpMass;
    a = { 0.f, 0.f };

    colour = inpCol;
    trailCol = inpTrailCol;

    trailHistory = std::vector<sf::Vector2f>();
}


void Planet::move() {

    trailHistory.push_back(body.getPosition());

    if (trailHistory.size() > TRAIL_LENGTH) {
        trailHistory.erase(trailHistory.begin()); // Remove the oldest point
    }

    v += a;
    body.move(v);
}

void Planet::draw(sf::RenderWindow& target, sf::Shader& shader) const{

    // Get world and screen positions
    sf::Vector2f worldPos = body.getPosition();

    // Create the glow effect
    sf::CircleShape glow(radius * 3.0f);
    glow.setOrigin({glow.getRadius(), glow.getRadius()});
    glow.setPosition(worldPos);

    // Convert the center position to screen coordinates for the shader
    sf::Vector2u windowSize = target.getSize();
    sf::Vector2f screenPos = static_cast<sf::Vector2f>(target.mapCoordsToPixel(worldPos));

    // Adjust for SFML's shader coordinate system (y-axis might be flipped)
    // OpenGL and SFML have different Y-axis origins
    screenPos.y = windowSize.y - screenPos.y;

    // Set the shader uniforms
    shader.setUniform("u_center", sf::Glsl::Vec2(screenPos));
    shader.setUniform("u_radius", radius * 3.0f);
    shader.setUniform("u_color", sf::Glsl::Vec4(colour));

    // Draw the glow effect with the shader
    sf::RenderStates states;
    states.shader = &shader;

    for (size_t i = 0; i < trailHistory.size(); ++i) {
        float alpha = static_cast<float>(i) / trailHistory.size(); 
        sf::CircleShape dot(TRAIL_SIZE); 
        dot.setPosition(trailHistory[i]);
        dot.setFillColor(sf::Color(trailCol.r, trailCol.g, trailCol.b, static_cast<uint8_t>(alpha * 255)));
        target.draw(dot);
    }




    target.draw(glow, states);

    // Draw the planet body without shader
    target.draw(body);
}
