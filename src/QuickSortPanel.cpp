#include "QuickSortPanel.hpp"
#include "config.hpp"
#include <algorithm>

QuickSortPanel::QuickSortPanel(sf::Vector2f pos, sf::Vector2f size, int numBars)
    : SortPanel(pos, size, numBars)
{
    if (values.size() > 1)
        callStack.push({0, static_cast<int>(values.size() - 1)});
}

bool QuickSortPanel::step() {
    // Done
    if (callStack.empty() && !partitioning)
        return false;

    if (!partitioning) {
        startNextPartition();
    }

    if (j < high) {
        if (values[j] < values[high]) {
            i++;
            std::swap(values[i], values[j]);
        }
        j++;
    } else {
        std::swap(values[i + 1], values[high]);
        pivotIndex = i + 1;
        finalizePartition();
        partitioning = false;
    }

    // 1. Update bar heights first
    updateBarGraphics();

    // 2. Then set colors
    for (auto& bar : bars)
        bar.setFillColor(DEFAULT_COLOR);

    if (partitioning) {
        if (j < high) {
            bars[high].setFillColor(sf::Color::Red);     // Pivot = red
            bars[j].setFillColor(sf::Color::Yellow);      // Current = yellow
            if (values[j] < values[high])
                bars[i].setFillColor(sf::Color::Green);   // Swapped = green
        }
    } else {
        if (pivotIndex >= 0 && pivotIndex < static_cast<int>(bars.size())) {
            bars[high].setFillColor(sf::Color::Red);               // old pivot
            bars[pivotIndex].setFillColor(SORTED_COLOR);           // final position
        }
    }

    return true;
}



void QuickSortPanel::startNextPartition() {
    auto range = callStack.top();
    callStack.pop();
    low = range.first;
    high = range.second;

    if (low < high) {
        partitioning = true;
        pivotIndex = high;
        i = low - 1;
        j = low;
    }
}

void QuickSortPanel::finalizePartition() {
    if (pivotIndex - 1 > low)
        callStack.push({low, pivotIndex - 1});
    if (pivotIndex + 1 < high)
        callStack.push({pivotIndex + 1, high});
}

