/**
 * designer.hpp defines the firework designer object (class)
 * it designs a given firework giving it random parameters/features
 */

#ifndef FIREWORKS_DESIGNER_HPP
#define FIREWORKS_DESIGNER_HPP

// FIXED FIREWORK PARAMETERS
#define MAX_ATOM_COUNT 2500 // number of atoms in a firework
#define MIN_ATOM_COUNT 100
#define MAX_SPEED 100 // travel speed of atoms
#define MIN_SPEED 0
#define MAX_ANGLE 360 // angle of travel of atoms
#define MIN_ANGLE 0
#define MAX_LIFE 3000 // lifetime of atoms
#define MIN_LIFE 2000

// FIXED LAUNCHER PARAMETERS
#define MAX_LAUNCH_LEN 200 // length of the launcher
#define MIN_LAUNCH_LEN 50
#define MAX_LAUNCH_SPEED 70 // travel speed of the launcher
#define MIN_LAUNCH_SPEED 40

#include "SFML/Graphics.hpp"
#include "physics.hpp"


/* === firework designer class definitions ========================== */
class FireworkDesigner { // designs parameters of a custom firework
    int atomCount; // fixed atom count of firework
    int angleDivCount; // angular divisions in a firework
    int speedDivCount; // speed divisions in firework (used for coloring)
    int colorMethodID; // coloring methodologies (random mixed, random single, angle based, speed based)
    int ageMethodID; // aging methodologies (fade, spark)
    std::vector<sf::Color> colors;

public:
    FireworkDesigner ();
    void setColors (int); // sets random number of colors to be used in design
    void aging (sf::Uint8&, sf::Time) const; // applies aging method
    // getter methods - fixed or random values based on given range or methodology
    static float getSpeed ();
    static sf::Time getLifetime ();
    int getAtomCount () const;
    float getAngle () const;
    sf::Color getColor (float, float);
};


/* === launcher designer class definitions ========================== */
class LauncherDesigner {
    int launchLen; // fixed length of launcher
    float launchSpeed; // fixed travel of speed
    sf::Color baseCol; // color of the launcher

public:
    LauncherDesigner ();
    // getter methods - fixed or random values based on given range
    int getLength () const;
    float getSpeed () const;
    sf::Color getColor ();
};


#endif
