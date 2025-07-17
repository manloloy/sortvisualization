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
    if (!isDragging) {
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
        isDragging = true;
        dragOffset = mousePos - shape.getPosition();
    }
    else if (event.type == sf::Event::MouseButtonReleased &&
             event.mouseButton.button == sf::Mouse::Left)
    {
        isDragging = false;
    }
    else if (event.type == sf::Event::MouseMoved && isDragging) {
        shape.setPosition(mousePos - dragOffset);
        label.setPosition(shape.getPosition() + sf::Vector2f(30.f, 20.f));
    }
}

bool FallingBlock::isBeingDragged() const {
    return isDragging;
}

void FallingBlock::setBeingDragged(bool dragged) {
    isDragging = dragged;
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
bool FallingBlock::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}

void FallingBlock::startDrag(const sf::Vector2f& mousePos) {
    isDragging = true;
    dragOffset = mousePos - shape.getPosition();  // changed to match handleEvent
}


void FallingBlock::drag(const sf::Vector2f& mousePos) {
    if (isDragging) {
        shape.setPosition(mousePos + dragOffset);
        label.setPosition(shape.getPosition() + sf::Vector2f(30.f, 20.f));  // add this line
    }
}


void FallingBlock::stopDrag() {
    isDragging = false;
}
void FallingBlock::setVelocity(const sf::Vector2f& v) {
    velocity = v;
}
