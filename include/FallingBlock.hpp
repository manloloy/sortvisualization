#ifndef FALLING_BLOCK_HPP
#define FALLING_BLOCK_HPP

#include <SFML/Graphics.hpp>

class FallingBlock {
public:
    FallingBlock(int value, sf::Vector2f position);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    bool isBeingDragged() const;
    void setBeingDragged(bool dragged);
    int getValue() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);

private:
    int value;
    sf::RectangleShape shape;
    sf::Text label;

    sf::Vector2f velocity;
    bool beingDragged = false;
    sf::Vector2f dragOffset;
};

#endif // FALLING_BLOCK_HPP
