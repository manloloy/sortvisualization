#include "SelectionSortPanel.hpp"
#include "config.hpp"
#include <algorithm>

SelectionSortPanel::SelectionSortPanel(sf::Vector2f pos, sf::Vector2f size, int numBars)
    : SortPanel(pos, size, numBars)
{}

bool SelectionSortPanel::step() {
    if (static_cast<size_t>(i) >= values.size())
        return false;

    // Reset all bar colors
    for (auto& bar : bars)
        bar.setFillColor(DEFAULT_COLOR);

    // Safe coloring (bounds checks)
    if (static_cast<size_t>(i) < bars.size())
        bars[i].setFillColor(SORTED_COLOR);
    
    if (static_cast<size_t>(minIndex) < bars.size())
        bars[minIndex].setFillColor(ACTIVE_COLOR);

    if (static_cast<size_t>(j) < values.size()) {
        if (values[j] < values[minIndex])
            minIndex = j;

        if (static_cast<size_t>(j) < bars.size())
            bars[j].setFillColor(sf::Color::Yellow);

        j++;
    } else {
        // Swap at the end of each pass
        if (minIndex != i)
            std::swap(values[i], values[minIndex]);

        i++;
        j = i + 1;
        minIndex = i;

        updateBarGraphics();
    }

    return true;
}