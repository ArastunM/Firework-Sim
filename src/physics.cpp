/**
 * physics.ccp implements the firework physics (physics.hpp) and randomizer functions
 */

#include "physics.hpp"


/* === randomizer definitions ========================== */
int fRand (int from, int to) {
    return (std::rand() % (to - from) + from);
}

sf::Vector2f randOrigin (unsigned int width, unsigned int height) {
    return {static_cast<float>(fRand(0, width)), static_cast<float>(height)};
}
sf::Color randColor () { // from 30 onwards to promote light fireworks
    sf::Color randCol(fRand(30, 255),
                      fRand(30, 255),
                      fRand(30, 255));
    return randCol;
}
sf::Color randDivColor (float current, float maxVal, int div, std::vector<sf::Color> colors) {
    // ratio allows providing same colors for division sections
    float ratio = maxVal / static_cast<float>(div);
    return colors[static_cast<int>(current / ratio)];
}


/* === physics function definitions ========================== */
sf::Vector2f getVelocity (float speed, float angle) {
    return {std::cos(angle) * speed, std::sin(angle) * speed};
}
float getAngle (sf::Vector2f origin, sf::Vector2f target) {
    return std::atan2(target.y - origin.y, target.x - origin.x);
}

void friction (sf::Vector2f& velocity, sf::Time elapsed) {
    sf::Vector2f friction = {-DRAG * elapsed.asSeconds() * velocity.x,
                             -DRAG * elapsed.asSeconds() * velocity.y};
    velocity += friction;
}
void gravity (sf::Vector2f& velocity, sf::Time elapsed) {
    velocity.y += GRAV * elapsed.asSeconds();
}
void fade (sf::Uint8& trn, sf::Time lifetime, float maxLife) {
    float ratio = lifetime.asSeconds() / (maxLife / 1000.f); // milliseconds to seconds
    trn = static_cast<sf::Uint8>(ratio * 255);
}
void spark (sf::Uint8& trn, sf::Time lifetime, float maxLife) {
    // ambiguous multiplications (3.14f * 6) are used to set ratio within sine range
    // this allows to simulate a spark (transparency changing like sine graph)
    float ratio = lifetime.asSeconds() / (maxLife / 1000.f) * 3.14f * 6;
    trn = static_cast<sf::Uint8>(std::sin(ratio) * 255);
}
