#include "SortRushScreen.hpp"
#include "config.hpp"
#include "AppManager.hpp"

SortRushScreen::SortRushScreen() {
    title.setFont(globalFont);
    title.setString("Sort Rush Mode (Press ESC to return)");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    title.setPosition(50, 50);
}

void SortRushScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        AppManager::getInstance().popScreen();
    }
}

void SortRushScreen::update(float) {}

void SortRushScreen::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(title);
}
