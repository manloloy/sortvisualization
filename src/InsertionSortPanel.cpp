#include "InsertionSortPanel.hpp"
#include "config.hpp"

#include <algorithm>

InsertionSortPanel::InsertionSortPanel(sf::Vector2f pos, sf::Vector2f size, int numBars)
    : SortPanel(pos, size, numBars)
{}

bool InsertionSortPanel::step() {
    if (i >= static_cast<int>(values.size()))
        return false;

    // Shift logic
    if (!keyHeld) {
        key = values[i];
        j = i - 1;
        keyHeld = true;
    }

    if (j >= 0 && values[j] > key) {
        values[j + 1] = values[j];
        j--;
    } else {
        values[j + 1] = key;
        i++;
        keyHeld = false;
    }

    // Sync heights before setting colors
    updateBarGraphics();

    // Reset to default first
    for (auto& bar : bars)
        bar.setFillColor(DEFAULT_COLOR);

    // Then apply coloring logic
    if (j >= 0 && values[j] > key) {
        bars[j].setFillColor(sf::Color::Yellow);
        bars[j + 1].setFillColor(sf::Color::Yellow);
    } else {
        if (i < static_cast<int>(bars.size()))
            bars[i].setFillColor(SORTED_COLOR);
    }

    return true;
}
