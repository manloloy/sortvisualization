#ifndef QUICK_SORT_PANEL_HPP
#define QUICK_SORT_PANEL_HPP

#include "SortPanel.hpp"
#include <stack>
#include <utility> // for std::pair

class QuickSortPanel : public SortPanel {
public:
    QuickSortPanel(sf::Vector2f pos, sf::Vector2f size, int numBars = 25);
    bool step() override;

private:
    std::stack<std::pair<int, int>> callStack; // Simulates recursion stack
    int low = -1, high = -1, pivotIndex = -1, i = -1, j = -1;
    bool partitioning = false;

    void startNextPartition();  // Pop from stack and setup state
    void finalizePartition();   // Push new ranges onto stack
};

#endif // QUICK_SORT_PANEL_HPP
