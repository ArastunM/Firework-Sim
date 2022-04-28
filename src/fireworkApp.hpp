/**
 * fireworkApp.hpp defines the fireworks app
 */

#ifndef FIREWORKS_FIREWORK_WIN_HPP
#define FIREWORKS_FIREWORK_WIN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "launcher.hpp"
#include "firework.hpp"


/* === firework app class definition ========================== */
class FireworkApp {
    sf::RenderWindow window;
    sf::Event event{};
    sf::Clock clock;
    std::vector<Launcher*> launchers; // stores all active launchers
    std::vector<Firework*> fireworks; // stores all active fireworks

    sf::Text notice;
    sf::Font noticeFont;
    bool noticeDisplay;
    float noticeTrn;
    sf::Sound soundLaunch;
    sf::SoundBuffer bufferLaunch;
    sf::Sound soundFirework;
    sf::SoundBuffer bufferFirework;

public:
    // initializing SFML window
    explicit FireworkApp (unsigned int width=800, unsigned int height=600);
    void launchWin ();
    void updateWin (sf::Time);
    // initializing Launchers and Fireworks
    void addLauncher ();
    void addFirework (sf::Vector2f target);

    // setting and using side features
    void setNotice ();
    void resetNotice (); // updates the transparency
    void setAudio ();
    void playRandLaunch (); // launch sound with random pitch
    void playRandExplosion (); // explosion with random pitch
};


#endif
