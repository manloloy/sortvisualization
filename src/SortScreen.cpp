// SortScreen.cpp
#include "SortScreen.hpp"
#include "AppManager.hpp"
#include "config.hpp"
#include "SortTypes.hpp"
#include <iostream>
#include "SortPanel.hpp"
#include "TestSortPanel.hpp"


SortScreen::SortScreen(const std::vector<SortAlgorithm>& selectedAlgos)
    : algorithms(selectedAlgos)
{
    label.setFont(globalFont);
    label.setString("Sorting Panel (press ESC to go back)");
    label.setCharacterSize(24);
    label.setPosition(50, 50);
    label.setFillColor(sf::Color::White);

    std::cout << "Selected algorithms:\n";
    for (auto algo : algorithms) {
        switch (algo) {
            case SortAlgorithm::Selection:
                std::cout << " - Selection Sort\n"; break;
            case SortAlgorithm::Insertion:
                std::cout << " - Insertion Sort\n"; break;
            case SortAlgorithm::Quick:
                std::cout << " - Quick Sort\n"; break;
            case SortAlgorithm::Merge:
                std::cout << " - Merge Sort\n"; break;
        }
    }

    testPanel = std::make_unique<TestSortPanel>(
        sf::Vector2f(100, 150),
        sf::Vector2f(800, 400)
    );
}
void SortScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        AppManager::getInstance().returnToMenu();
    }
}

void SortScreen::update(float dt) {
    testPanel->update(dt);
}

void SortScreen::draw(sf::RenderWindow& window) {
    window.draw(label);
    testPanel->draw(window);

}
