#ifndef SORT_RUSH_SCREEN_HPP
#define SORT_RUSH_SCREEN_HPP

#include "Screen.hpp"
#include <SFML/Graphics.hpp>

class SortRushScreen : public Screen {
public:
    SortRushScreen();
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Text title;
};

#endif
