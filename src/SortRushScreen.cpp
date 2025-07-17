#include "SortRushScreen.hpp"
#include "config.hpp"
#include "AppManager.hpp"

SortRushScreen::SortRushScreen() {
    // Optionally seed randomness
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    dropZone.setSize(sf::Vector2f(WINDOW_WIDTH, 100));
    dropZone.setPosition(0, WINDOW_HEIGHT - 100);
    dropZone.setFillColor(sf::Color(50, 50, 150, 150));  // semi-transparent blue


}

void SortRushScreen::handleEvent(const sf::Event& event) {
    auto& window = AppManager::getInstance().getWindow();
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        for (auto it = blocks.rbegin(); it != blocks.rend(); ++it) {
            if (it->contains(mousePos)) {
                it->startDrag(mousePos);
                break;
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        for (auto& block : blocks) {
            if (block.isBeingDragged()) {
                block.stopDrag();
                break;
            }
        }
    }

    if (event.type == sf::Event::MouseMoved) {
        for (auto& block : blocks) {
            if (block.isBeingDragged()) {
                block.drag(mousePos);
                break;
            }
        }
    }

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
    window.draw(dropZone);
    for (auto& block : blocks)
        block.draw(window);
    }