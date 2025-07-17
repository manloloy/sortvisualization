#ifndef SORT_SCREEN_HPP
#define SORT_SCREEN_HPP

#include "Screen.hpp"
#include "SortTypes.hpp"
#include "SortPanel.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class SortScreen : public Screen {
public:
    SortScreen(const std::vector<SortAlgorithm>& selectedAlgos);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    std::vector<SortAlgorithm> algorithms;
    std::vector<std::unique_ptr<SortPanel>> panels; // ✅ NEW

    sf::Text label;

    float stepDelay = 0.15f;
    float timeSinceLastStep = 0.0f;
};

#endif // SORT_SCREEN_HPP
