#include "MergeSortPanel.hpp"
#include "config.hpp"

MergeSortPanel::MergeSortPanel(sf::Vector2f pos, sf::Vector2f size, int numBars)
    : SortPanel(pos, size, numBars)
{
    temp = values;
    prepareNextPass();
}

void MergeSortPanel::prepareNextPass() {
    for (int i = 0; i < static_cast<int>(values.size()); i += 2 * mergeSize) {
        int mid = std::min(i + mergeSize, static_cast<int>(values.size()));
        int right = std::min(i + 2 * mergeSize, static_cast<int>(values.size()));
        if (mid < right) {
            tasks.push({i, mid, right});
        }
    }

    if (tasks.empty()) {
        values = temp;
        updateBarGraphics();
    }

    mergeSize *= 2;
}

bool MergeSortPanel::step() {
    // Done
    if (mergeSize / 2 > static_cast<int>(values.size()))
        return false;

    // Reset all colors
    for (auto& bar : bars)
        bar.setFillColor(DEFAULT_COLOR);

    if (!tasks.empty()) {
        MergeTask& task = tasks.front();

        if (!task.initialized) {
            task.leftPart = std::vector<int>(temp.begin() + task.left, temp.begin() + task.mid);
            task.rightPart = std::vector<int>(temp.begin() + task.mid, temp.begin() + task.right);
            task.i = task.j = 0;
            task.k = task.left;
            task.initialized = true;
            // Highlight pivot (midpoint) once it's initialized
            if (task.mid < static_cast<int>(bars.size()))
                bars[task.mid].setFillColor(sf::Color::Magenta);
            }

        // Perform merge step
        if (task.i < static_cast<int>(task.leftPart.size()) && task.j < static_cast<int>(task.rightPart.size())) {
            if (task.leftPart[task.i] <= task.rightPart[task.j]) {
                values[task.k] = task.leftPart[task.i];
                updateBarGraphics();  // update size first
                bars[task.k].setFillColor(sf::Color::Green);  // then set color
                task.i++;
            } else {
                values[task.k] = task.rightPart[task.j];
                updateBarGraphics();
                bars[task.k].setFillColor(sf::Color::Yellow);
                task.j++;
            }
            task.k++;
        }
        else if (task.i < static_cast<int>(task.leftPart.size())) {
            values[task.k] = task.leftPart[task.i];
            updateBarGraphics();
            bars[task.k].setFillColor(sf::Color::Green);
            task.i++;
            task.k++;
        }
        else if (task.j < static_cast<int>(task.rightPart.size())) {
            values[task.k] = task.rightPart[task.j];
            updateBarGraphics();
            bars[task.k].setFillColor(sf::Color::Yellow);
            task.j++;
            task.k++;
        }
        else {
            tasks.pop();  // Task complete
        }

        return true;
    }
    else {
        temp = values;
        prepareNextPass();
        return true;
    }
}
