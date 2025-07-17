// SortScreen.cpp
#include "SortScreen.hpp"
#include "AppManager.hpp"
#include "config.hpp"
#include "SortTypes.hpp"
#include <iostream>
#include "SortPanel.hpp"

#include "TestSortPanel.hpp"
#include "SelectionSortPanel.hpp"
#include "InsertionSortPanel.hpp"
#include "QuickSortPanel.hpp"
#include "MergeSortPanel.hpp"


// Helper function to calculate grid-based panel position
sf::Vector2f calculatePanelPosition(int index, int totalPanels) {
    int cols = (totalPanels <= 2) ? totalPanels : 2;
    int rows = (totalPanels + 1) / 2;

    float panelWidth = WINDOW_WIDTH / cols;
    float panelHeight = (WINDOW_HEIGHT - 150) / rows;

    int row = index / cols;
    int col = index % cols;

    float x = col * panelWidth;
    float y = 120 + row * panelHeight;

    return sf::Vector2f(x, y);
}

SortScreen::SortScreen(const std::vector<SortAlgorithm>& selectedAlgos)
    : algorithms(selectedAlgos)
{
    label.setFont(globalFont);
    label.setString("Sorting Panel (press ESC to go back)");
    label.setCharacterSize(24);
    label.setPosition(50, 50);
    label.setFillColor(sf::Color::White);

    for (size_t i = 0; i < algorithms.size(); ++i) {
        sf::Vector2f panelSize(400, 300);
        sf::Vector2f position = calculatePanelPosition(i, algorithms.size());

        std::unique_ptr<SortPanel> panel;

        switch (algorithms[i]) {
            case SortAlgorithm::Selection:
                panel = std::make_unique<SelectionSortPanel>(position, panelSize);
                break;
            case SortAlgorithm::Insertion:
                panel = std::make_unique<InsertionSortPanel>(position, panelSize);
                break;
            case SortAlgorithm::Quick:
                panel = std::make_unique<QuickSortPanel>(position, panelSize);
                break;
            case SortAlgorithm::Merge:
                panel = std::make_unique<MergeSortPanel>(position, panelSize);
                break;
        }

        panels.push_back(std::move(panel));
    }
}



void SortScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        AppManager::getInstance().returnToMenu();
    }
}

void SortScreen::update(float dt) {
    timeSinceLastStep += dt;

    if (timeSinceLastStep >= stepDelay) {
        for (auto& panel : panels)
            panel->step();

        timeSinceLastStep = 0.0f;
    }

    for (auto& panel : panels)
        panel->update(dt);
}

void SortScreen::draw(sf::RenderWindow& window) {
    window.clear(BG_COLOR);
    window.draw(label);

    float separatorThickness = 4.0f;
    sf::Color sepColor = sf::Color::Blue;

    // Draw all panels
    for (auto& panel : panels)
        panel->draw(window);

    if (panels.empty()) return;

    // Calculate layout
    int totalPanels = panels.size();
    int columns = std::min(totalPanels, 2);               // max 2 per row
    int rows = (totalPanels + columns - 1) / columns;     // ceil(total / columns)

    // Horizontal separators
    for (int row = 0; row <= rows; ++row) {
        int index = std::min(row * columns, totalPanels - 1);
        float y;

        if (row == 0) {
            y = panels[index]->getPosition().y;
        } else if (row == rows) {
            y = panels[index]->getPosition().y + panels[index]->getSize().y;
        } else {
            y = panels[index]->getPosition().y;
        }

        float xStart = panels[0]->getPosition().x;
        float xEnd = panels[std::min(columns - 1, totalPanels - 1)]->getPosition().x +
                     panels[std::min(columns - 1, totalPanels - 1)]->getSize().x;

        sf::RectangleShape hLine(sf::Vector2f(xEnd - xStart, separatorThickness));
        hLine.setPosition(xStart, y - separatorThickness / 2);
        hLine.setFillColor(sepColor);
        window.draw(hLine);
    }

    // Vertical separators
    for (int row = 0; row < rows; ++row) {
        int startIdx = row * columns;
        int endIdx = std::min(startIdx + columns, totalPanels);

        for (int col = 0; col <= (endIdx - startIdx); ++col) {
            int idx;
            if (col == 0)
                idx = startIdx;
            else if (col == (endIdx - startIdx))
                idx = endIdx - 1;
            else
                idx = startIdx + col;

            float x;
            if (col == 0) {
                x = panels[idx]->getPosition().x;
            } else if (col == (endIdx - startIdx)) {
                x = panels[idx]->getPosition().x + panels[idx]->getSize().x;
            } else {
                x = panels[idx]->getPosition().x;
            }

            float y = panels[idx]->getPosition().y;
            float height = panels[idx]->getSize().y;

            sf::RectangleShape vLine(sf::Vector2f(separatorThickness, height));
            vLine.setPosition(x - separatorThickness / 2, y);
            vLine.setFillColor(sepColor);
            window.draw(vLine);
        }
    }
}



