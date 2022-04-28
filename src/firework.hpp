/**
 * firework.hpp defines the firework object (class)
 */

#ifndef FIREWORKS_FIREWORK_HPP
#define FIREWORKS_FIREWORK_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include "designer.hpp"
#include "physics.hpp"


/* === firework class definition ========================== */
class Firework: public sf::Drawable, public sf::Transformable {
protected:
    struct Atom { // individual atom in a firework explosion
        sf::Vector2f velocity;
        sf::Time lifetime;
    };
    std::vector<Atom> atoms;
    sf::VertexArray f_vertices; // drawable storage of atoms
    sf::Vector2f target; // point of explosion

    bool isActive = false;
    FireworkDesigner designer;

    virtual void setAtom (unsigned int);
    void draw (sf::RenderTarget&, sf::RenderStates) const override;

public:
    explicit Firework ();
    ~Firework () override;
    virtual void ignite (sf::Vector2f); // sets up target and atoms, ignites
    virtual void update (sf::Time);
    // getter method
    bool getActive () const;
};


#endif
