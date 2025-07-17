#include "FallingBlock.hpp"
#include "config.hpp" // for globalFont

FallingBlock::FallingBlock(int value, sf::Vector2f position)
    : value(value)
{
    shape.setSize({60.f, 60.f});
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position);

    label.setFont(globalFont);
    label.setString(std::to_string(value));
    label.setCharacterSize(20);
    label.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = label.getLocalBounds();
    label.setOrigin(textBounds.width / 2, textBounds.height / 2);
    label.setPosition(position + sf::Vector2f(30.f, 20.f)); // center inside block

    velocity = {0.f, 150.f}; // falling speed
}

void FallingBlock::update(float dt) {
    if (!beingDragged) {
        shape.move(velocity * dt);
        label.move(velocity * dt);
    }
}

void FallingBlock::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}

void FallingBlock::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        shape.getGlobalBounds().contains(mousePos))
    {
        beingDragged = true;
        dragOffset = mousePos - shape.getPosition();
    }
    else if (event.type == sf::Event::MouseButtonReleased &&
             event.mouseButton.button == sf::Mouse::Left)
    {
        beingDragged = false;
    }
    else if (event.type == sf::Event::MouseMoved && beingDragged) {
        shape.setPosition(mousePos - dragOffset);
        label.setPosition(shape.getPosition() + sf::Vector2f(30.f, 20.f));
    }
}

bool FallingBlock::isBeingDragged() const {
    return beingDragged;
}

void FallingBlock::setBeingDragged(bool dragged) {
    beingDragged = dragged;
}

int FallingBlock::getValue() const {
    return value;
}

sf::FloatRect FallingBlock::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f FallingBlock::getPosition() const {
    return shape.getPosition();
}

void FallingBlock::setPosition(const sf::Vector2f& pos) {
    shape.setPosition(pos);
    label.setPosition(pos + sf::Vector2f(30.f, 20.f));
}
