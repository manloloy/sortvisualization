#ifndef SORT_PANEL_HPP
#define SORT_PANEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class SortPanel {
public:
    SortPanel(sf::Vector2f position, sf::Vector2f size, int numBars = 25);
    virtual ~SortPanel() = default;

    virtual bool step() = 0; // perform one step; returns false if sorting is complete

    void update(float dt);
    void draw(sf::RenderWindow& window);

protected:
    std::vector<int> values;                // bar values
    std::vector<sf::RectangleShape> bars;   // visual bars
    sf::Vector2f origin;
    sf::Vector2f panelSize;

    void updateBarGraphics(); // sync bar heights/colors with values
    void shuffleValues();     // generate random values
};

#endif // SORT_PANEL_HPP
