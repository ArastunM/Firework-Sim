/**
 * designer.ccp implements the firework designer (designer.hpp) functions
 */

#include "designer.hpp"


/* === firework designer class implementation ========================== */
FireworkDesigner::FireworkDesigner() {
    // setting initial parameters based on fixed ranges
    atomCount = fRand(MIN_ATOM_COUNT, MAX_ATOM_COUNT);
    angleDivCount = fRand(1, 10);
    speedDivCount = fRand(1, 6);
    colorMethodID = fRand(0, 4); // 0 to 4 coloring methods
    ageMethodID = fRand(0, 2); // 0 to 2 aging methods
    setColors(angleDivCount + speedDivCount);
}

void FireworkDesigner::setColors(int div) {
    for (unsigned int i = 0; i < div; i++) {
        colors.push_back(randColor());
    }
}

void FireworkDesigner::aging(sf::Uint8& trn, sf::Time lifetime) const {
    if (ageMethodID == 0) spark(trn, lifetime, MAX_LIFE);
    else fade(trn, lifetime, MAX_LIFE);
}

float FireworkDesigner::getSpeed() {
    return static_cast<float>(fRand(MIN_SPEED, MAX_SPEED));
}

sf::Time FireworkDesigner::getLifetime() {
    return sf::milliseconds(fRand(MIN_LIFE, MAX_LIFE));
}

int FireworkDesigner::getAtomCount() const {
    return atomCount;
}

float FireworkDesigner::getAngle() const {
    int randAngle = fRand(MIN_ANGLE, MAX_ANGLE);
    // ensuring selection is within angle division range
    while (randAngle % angleDivCount != 0) {
        randAngle = fRand(MIN_ANGLE, MAX_ANGLE);
    } return static_cast<float>(randAngle);
}

sf::Color FireworkDesigner::getColor(float speed, float angle) {
    if (colorMethodID == 0) return randColor();
    else if (colorMethodID == 1) return colors[0];
    else if (colorMethodID == 2) return randDivColor(speed, MAX_SPEED, speedDivCount, colors);
    else return randDivColor(angle, MAX_ANGLE, angleDivCount, colors);
}

/* === launcher designer class implementation ========================== */
LauncherDesigner::LauncherDesigner() {
    // setting initial parameters
    launchLen = fRand(MIN_LAUNCH_LEN, MAX_LAUNCH_LEN);
    launchSpeed = static_cast<float>(fRand(MIN_LAUNCH_SPEED, MAX_LAUNCH_SPEED)) * 0.01f;
    baseCol = randColor();
}

int LauncherDesigner::getLength() const {
    return launchLen;
}

float LauncherDesigner::getSpeed() const {
    return launchSpeed;
}

sf::Color LauncherDesigner::getColor() {
    return baseCol;
}
