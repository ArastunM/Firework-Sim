/**
 * fireworkApp.ccp implements firework simulator main app (fireworkApp.hpp) functions
 */

#include "fireworkApp.hpp"


/* === firework app class implementation ========================== */
FireworkApp::FireworkApp (unsigned int width, unsigned int height) {
    window.create(sf::VideoMode(width, height),
                  "Firework Simulator",sf::Style::Close);
    noticeDisplay = true;
    noticeTrn = 0;
    setNotice();
    setAudio();
}

void FireworkApp::launchWin() {
    // main loop (runs as long as main window is open)
    while (window.isOpen()) {
        // event loop (checks for triggered events in every iteration)
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                noticeDisplay = false;
                addLauncher();
            }
        }

        // pixel update operations
        window.clear(sf::Color(0, 0, 10)); // night sky color
        // updating the window
        sf::Time elapsed = clock.restart();
        updateWin(elapsed);
        window.display();
    }
}

void FireworkApp::updateWin(sf::Time elapsed) {
    if (noticeDisplay) { resetNotice(); window.draw(notice); }

    // updating all active launchers
    for (unsigned int i = 0; i < launchers.size(); i++) {
        if (launchers[i]->getActive()) {
            launchers[i]->update(elapsed);
            window.draw(*launchers[i]);
        } else { // deleting finished launcher, adding its firework
            addFirework(launchers[i]->getTarget());
            delete launchers[i];
            launchers.erase(launchers.begin() + i);
        }
    }
    // updating all active fireworks
    for (unsigned int i = 0; i < fireworks.size(); i++) {
        if (fireworks[i]->getActive()) {
            fireworks[i]->update(elapsed);
            window.draw(*fireworks[i]);
        } else { // deleting the firework if it is finished
            delete fireworks[i];
            fireworks.erase(fireworks.begin() + i);
        }
    }
}

void FireworkApp::addLauncher() {
    // setting up a new launcher on mouse click (as target)
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    auto * launcher = new Launcher(window.getSize().x, window.getSize().y);
    launchers.push_back(launcher);
    launcher->launch(window.mapPixelToCoords(mouse));
    playRandLaunch();
}

void FireworkApp::addFirework(sf::Vector2f target) {
    // setting up a new firework on mouse click
    auto * firework = new Firework();
    fireworks.push_back(firework);
    firework->ignite(target);
    playRandExplosion();
}

void FireworkApp::setNotice() {
    if (!noticeFont.loadFromFile("fonts/anita_square.ttf")) {
        fprintf(stderr, "font could not be loaded\n");
    }
    notice.setFont(noticeFont);
    notice.setCharacterSize(20);
    notice.setString("CLICK TO LAUNCH A FIREWORK");
    noticeTrn = notice.getFillColor().a;
    resetNotice();

    // transforming the text
    sf::FloatRect textRect = notice.getLocalBounds();
    notice.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    notice.setPosition(sf::Vector2f(static_cast<float>((window.getSize().x)) / 2,
                                    (static_cast<float>(window.getSize().y)) / 5.f));
}

void FireworkApp::resetNotice () {
    noticeTrn += 0.1f;
    notice.setFillColor(sf::Color(255, 255, 255,
                                  static_cast<sf::Uint8>(noticeTrn)));
}

void FireworkApp::setAudio() {
    if (!bufferLaunch.loadFromFile("audio/sample_launch.wav")) exit(1);
    if (!bufferFirework.loadFromFile("audio/sample_explosion.wav")) exit(1);

    soundLaunch.setBuffer(bufferLaunch);
    soundLaunch.setVolume(50.f);
    soundFirework.setBuffer(bufferFirework);
    soundFirework.setVolume(150.f);
}

void FireworkApp::playRandLaunch() {
    soundLaunch.setPitch(static_cast<float>(fRand(75, 135)) * 0.01f);
    soundLaunch.play();
}

void FireworkApp::playRandExplosion() {
    soundFirework.setPitch(static_cast<float>(fRand(30, 250)) * 0.01f);
    soundFirework.play();
}
