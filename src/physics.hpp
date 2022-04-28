/**
 * physics.hpp defines the firework physics and randomizer functions
 * utilized by the designer, launcher and firework classes
 */

#ifndef FIREWORKS_PHYSICS_HPP
#define FIREWORKS_PHYSICS_HPP

// PHYSICS PARAMETERS:
#define DRAG 1.f // drag coefficient of air (friction)
#define GRAV 20.f // gravitational force

#include <cmath>
#include <SFML/Graphics.hpp>


/* === randomizer prototypes ========================== */
int fRand (int, int); // helper function for std::rand()
sf::Vector2f randOrigin (unsigned int, unsigned int);
sf::Color randColor (); // random atom color
sf::Color randDivColor (float current, float maxVal, int div, std::vector<sf::Color> colors);


/* === physics function prototypes ========================== */
sf::Vector2f getVelocity (float, float); // returns 2D velocity based on speed and angle
float getAngle (sf::Vector2f, sf::Vector2f); // returns angle based on origin and target
void friction (sf::Vector2f&, sf::Time); // applies friction to given velocity
void gravity (sf::Vector2f&, sf::Time); // applies gravity to given velocity
void fade (sf::Uint8&, sf::Time, float); // applies fade to atoms using atom lifetime
void spark (sf::Uint8&, sf::Time, float); // applies spark to atoms using atom lifetime


#endif
