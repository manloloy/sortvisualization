// include/Button.hpp
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button(const std::string& text, sf::Vector2f position, sf::Vector2f size);

    void setCallback(std::function<void()> callback);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    const sf::RectangleShape& getShape() const;
    const sf::Text& getLabel() const;

private:
    sf::RectangleShape shape;
    sf::Text label;

    sf::Color idleColor = sf::Color(70, 70, 70);
    sf::Color hoverColor = sf::Color(100, 100, 100);
    sf::Color textColor = sf::Color::White;

    bool isHovered = false;
    std::function<void()> onClick;
};

#endif // BUTTON_HPP
