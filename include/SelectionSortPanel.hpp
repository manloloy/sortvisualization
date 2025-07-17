#ifndef SELECTION_SORT_PANEL_HPP
#define SELECTION_SORT_PANEL_HPP

#include "SortPanel.hpp"

class SelectionSortPanel : public SortPanel {
public:
    SelectionSortPanel(sf::Vector2f position, sf::Vector2f size, int numBars = 25);

    bool step() override;

private:
    int i = 0;         // outer loop
    int j = 1;         // scanning index
    int minIndex = 0;  // current minimum
    bool swapping = false;
};

#endif // SELECTION_SORT_PANEL_HPP
