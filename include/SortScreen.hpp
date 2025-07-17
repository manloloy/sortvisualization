// SortScreen.hpp
#ifndef SORT_SCREEN_HPP
#define SORT_SCREEN_HPP

#include "Screen.hpp"
#include "SortTypes.hpp"
#include "SortPanel.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class SortScreen : public Screen {
public:
    SortScreen(const std::vector<SortAlgorithm>& selectedAlgos);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    float stepDelay = 0.2f;      // seconds between steps
    float timeSinceLastStep = 0.0f;
    sf::Font font;
    sf::Text label;
    std::vector<SortAlgorithm> algorithms;
    std::unique_ptr<SortPanel> testPanel;

};

#endif
