#ifndef TEST_SORT_PANEL_HPP
#define TEST_SORT_PANEL_HPP

#include "SortPanel.hpp"

class TestSortPanel : public SortPanel {
public:
    TestSortPanel(sf::Vector2f position, sf::Vector2f size, int numBars = 25)
        : SortPanel(position, size, numBars) {}

    bool step() override {
        return false;
    }
};

#endif
