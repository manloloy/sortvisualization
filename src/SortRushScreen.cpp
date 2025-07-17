#include "SortRushScreen.hpp"
#include "config.hpp"
#include "AppManager.hpp"

SortRushScreen::SortRushScreen() {
    // Optionally seed randomness
    std::srand(static_cast<unsigned>(std::time(nullptr)));

}

void SortRushScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        AppManager::getInstance().returnToMenu();
    }
}

void SortRushScreen::update(float dt) {
    spawnTimer += dt;

    if (spawnTimer >= spawnInterval) {
        int value = std::rand() % 100; // random value for block
        float x = 50.f + static_cast<float>(std::rand() % 900); // random x within window width

        blocks.emplace_back(value, sf::Vector2f(x, 0.f));
        spawnTimer = 0.0f;
    }

    for (auto& block : blocks)
        block.update(dt);
}

void SortRushScreen::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    for (auto& block : blocks)
        block.draw(window);
}