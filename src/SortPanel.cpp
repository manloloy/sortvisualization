#include "SortPanel.hpp"
#include <algorithm>
#include <random>
#include "config.hpp"

SortPanel::SortPanel(sf::Vector2f position, sf::Vector2f size, int numBars)
    : origin(position), panelSize(size)
{
    values.resize(numBars);
    bars.resize(numBars);
    shuffleValues();
    updateBarGraphics();
}

void SortPanel::shuffleValues() {
    for (size_t i = 0; i < values.size(); ++i)
        values[i] = static_cast<int>(i + 1);


    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(values.begin(), values.end(), g);
}

void SortPanel::updateBarGraphics() {
    float barWidth = panelSize.x / values.size();
    float maxHeight = panelSize.y;

    for (size_t i = 0; i < values.size(); ++i) {
        float heightRatio = static_cast<float>(values[i]) / values.size();
        float barHeight = heightRatio * maxHeight;

        sf::RectangleShape& bar = bars[i];
        bar.setSize({barWidth - 2.0f, barHeight}); // 2 px gap
        bar.setPosition(origin.x + i * barWidth, origin.y + (panelSize.y - barHeight));
        bar.setFillColor(DEFAULT_COLOR);
    }
}

void SortPanel::update(float dt) {
    // Optional for animation control
}

void SortPanel::draw(sf::RenderWindow& window) {
    for (const auto& bar : bars)
        window.draw(bar);
}
