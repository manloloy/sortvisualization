#ifndef INSERTION_SORT_PANEL_HPP
#define INSERTION_SORT_PANEL_HPP

#include "SortPanel.hpp"

class InsertionSortPanel : public SortPanel {
public:
    InsertionSortPanel(sf::Vector2f pos, sf::Vector2f size, int numBars = 25);
    bool step() override;

private:
    int i = 1;
    int j = 0;
    int key = 0;
    bool keyHeld = false;
};

#endif
