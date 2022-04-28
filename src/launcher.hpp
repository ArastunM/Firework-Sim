/**
 * launcher.hpp defines the firework launcher object (class)
 */

#ifndef FIREWORKS_LAUNCHER_HPP
#define FIREWORKS_LAUNCHER_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include "designer.hpp"
#include "physics.hpp"


/* === class definitions ========================== */
class Launcher: public sf::Drawable, public sf::Transformable {
    sf::VertexArray l_vertices;
    sf::Vector2f velocity;
    sf::Vector2f origin; // origin of the launcher (random)
    sf::Vector2f target; // planned explosion location

    bool isActive = false;
    LauncherDesigner designer;

    void setPoint (unsigned int);
    void draw (sf::RenderTarget&, sf::RenderStates) const override;

public:
    explicit Launcher (unsigned int, unsigned int);
    ~Launcher () override;
    void launch (sf::Vector2f); // sets up origin, target and launches
    void update (sf::Time);
    // getter methods
    bool getActive () const;
    sf::Vector2f getTarget();
};


#endif
