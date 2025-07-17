// src/Button.cpp
#include "Button.hpp"
#include "config.hpp"

Button::Button(const std::string& text, sf::Vector2f position, sf::Vector2f size) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(idleColor);

    label.setFont(globalFont);
    label.setString(text);
    label.setCharacterSize(20);
    label.setFillColor(textColor);

    // Center the label in the button
    sf::FloatRect textBounds = label.getLocalBounds();
    label.setOrigin(textBounds.left + textBounds.width / 2.0f,
                    textBounds.top + textBounds.height / 2.0f);
    label.setPosition(
        position.x + size.x / 2.0f,
        position.y + size.y / 2.0f
    );
}

void Button::setCallback(std::function<void()> callback) {
    onClick = callback;
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
    bool hovered = shape.getGlobalBounds().contains(mousePos);

    isHovered = hovered;
    shape.setFillColor(hovered ? hoverColor : idleColor);

    if (hovered && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (onClick) onClick();
 
    }
}

const sf::RectangleShape& Button::getShape() const {
    return shape;
}

const sf::Text& Button::getLabel() const {
    return label;
}


void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}
