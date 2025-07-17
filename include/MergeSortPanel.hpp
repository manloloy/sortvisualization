#ifndef MERGE_SORT_PANEL_HPP
#define MERGE_SORT_PANEL_HPP

#include "SortPanel.hpp"
#include <queue>

class MergeSortPanel : public SortPanel {
public:
    MergeSortPanel(sf::Vector2f pos, sf::Vector2f size, int numBars = 25);

    bool step() override;

private:
    struct MergeTask {
        int left, mid, right;
        int i, j, k;
        std::vector<int> leftPart, rightPart;
        bool initialized = false;
    };

    std::queue<MergeTask> tasks;
    std::vector<int> temp;
    int mergeSize = 1;
    bool initialized = false;

    void prepareNextPass();
};

#endif // MERGE_SORT_PANEL_HPP
