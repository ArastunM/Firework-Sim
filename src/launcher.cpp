/**
 * launcher.ccp implements the firework launcher (launcher.hpp) functions
 */

#include "launcher.hpp"


/* === class implementation ========================== */
void Launcher::setPoint(unsigned int index) {
    // setting initial launcher point parameters based on index
    auto f_index = static_cast<float>(index);
    l_vertices[index].position = origin + (velocity * f_index);
    float ratio = 255.f / static_cast<float>(designer.getLength());
    l_vertices[index].color = designer.getColor();
    l_vertices[index].color.a = static_cast<sf::Uint8>(f_index * ratio);
}

void Launcher::draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = nullptr; // no texture used
    renderTarget.draw(l_vertices, states);
}

Launcher::Launcher (unsigned int windWidth, unsigned int winHeight) {
    l_vertices = sf::VertexArray(sf::Points, designer.getLength());
    origin = randOrigin(windWidth, winHeight);
}

void Launcher::launch(sf::Vector2f toPosition) {
    target = toPosition;
    velocity = getVelocity(designer.getSpeed(), getAngle(origin, target));
    for (unsigned int i = 0; i < designer.getLength(); i++) {
        setPoint(i);
    }
    isActive = true; // ready for launch
}

void Launcher::update(sf::Time elapsed) {
    if (l_vertices[designer.getLength() - 1].position.y <= target.y) {
        isActive = false; // target has been reached
        return;
    }
    for (unsigned int i = 0; i < designer.getLength(); i++) {
        l_vertices[i].position += velocity * elapsed.asSeconds() * 700.f;
    }
}

bool Launcher::getActive() const {
    return isActive;
}

sf::Vector2f Launcher::getTarget() {
    return target;
}

Launcher::~Launcher() = default;
