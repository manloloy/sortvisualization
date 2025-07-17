// include/SelectionScreen.hpp
#ifndef SELECTION_SCREEN_HPP
#define SELECTION_SCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "SortTypes.hpp"

#include <SFML/Graphics.hpp>
#include <vector>


class SelectionScreen : public Screen {
public:
    SelectionScreen();

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Text prompt;
    Button startButton;
    Button sortRushButton;

    // Algorithm selection buttons
    std::vector<Button> algoButtons;
    std::vector<bool> algoSelected; // same size as algoButtons
    
    std::vector<SortAlgorithm> selectedAlgos; // what gets passed to SortScreen


};

#endif // SELECTION_SCREEN_HPP
