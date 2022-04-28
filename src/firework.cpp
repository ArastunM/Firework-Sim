/**
 * firework.ccp implements the firework (firework.hpp) functions
 */

#include "firework.hpp"


/* === firework class implementation ========================== */
void Firework::setAtom (unsigned int index) {
    // setting an atom is giving an individual atom starting parameters
    float speed = FireworkDesigner::getSpeed();
    float angle = designer.getAngle();
    atoms[index].velocity = getVelocity(speed, angle);
    atoms[index].lifetime = FireworkDesigner::getLifetime();
    // resetting the position of corresponding vertex
    f_vertices[index].position = target;
    f_vertices[index].color = designer.getColor(speed, angle);
}

void Firework::draw (sf::RenderTarget& renderTarget, sf::RenderStates states) const {
    // overriding window.draw for Firework
    states.transform *= getTransform();
    states.texture = nullptr; // no texture used
    renderTarget.draw(f_vertices, states);
}

Firework::Firework () { // constructing the firework
    // count number of total atoms
    atoms = std::vector<Atom>(designer.getAtomCount());
    // vertices are count number of points
    f_vertices = sf::VertexArray(sf::Points, designer.getAtomCount());
}

void Firework::ignite (sf::Vector2f atPosition) {
    target = atPosition;
    for (unsigned int i = 0; i < atoms.size(); i++) {
        setAtom(i);
    }
    isActive = true; // firework ready for explosion
}

void Firework::update (sf::Time elapsed) {
    // updates every atom of the system after elapsed time
    for (unsigned int i = 0; i < atoms.size(); i++) {
        Atom& atom = atoms[i];
        // updating atom position and lifetime
        f_vertices[i].position += atom.velocity * elapsed.asSeconds();
        atom.lifetime -= elapsed;
        if (atom.lifetime <= sf::Time::Zero) { isActive = false; continue; }
        else isActive = true;

        // applying physics rules (air friction, gravity)
        friction(atom.velocity, elapsed);
        gravity(atom.velocity, elapsed);
        designer.aging(f_vertices[i].color.a, atom.lifetime);
    }
}

bool Firework::getActive () const {
    return isActive;
}

Firework::~Firework () = default;
