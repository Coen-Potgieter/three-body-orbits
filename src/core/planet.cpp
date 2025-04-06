

#include "../include/planet.h"



Planet::Planet(sf::Vector2f initialVelocity, sf::Vector2f initialPos, float inpMass, float inpRadius, sf::Color inpCol, sf::Color inpTrailCol, size_t inpTrailLength) {

    radius = inpRadius;

    body = sf::CircleShape(inpRadius);
    body.setPosition(initialPos);
    body.setOrigin({ radius, radius });

    v = initialVelocity;
    mass = inpMass;
    a = { 0.f, 0.f };

    colour = inpCol;
    trailCol = inpTrailCol;

    /* body.setFillColor(colour); */
    /* body.setFillColor(sf::Color::Black); */
    body.setFillColor(sf::Color::White);

    trailHistory = std::vector<sf::Vector2f>();
    trailLength = inpTrailLength;
}


void Planet::move(sf::Vector2f correction) {


    v += a;
    body.move(v + correction);

    trailHistory.push_back(body.getPosition());

    if (trailHistory.size() > trailLength) {
        trailHistory.erase(trailHistory.begin()); // Remove the oldest point
    }
}

void Planet::draw(sf::RenderWindow& target, sf::Shader& shader) const{

    // Get world and screen positions
    sf::Vector2f worldPos = body.getPosition();

    // Create the glow effect
    float brightness = 5;
    sf::CircleShape glow(radius * brightness);
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
    shader.setUniform("u_radius", radius * brightness);
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
