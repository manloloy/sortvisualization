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

// helper function
sf::Vector2f calculatePanelPosition(int index, int totalPanels, sf::Vector2f panelSize) {
    if (totalPanels == 1) {
        float x = (WINDOW_WIDTH - panelSize.x) / 2;
        float y = (WINDOW_HEIGHT - panelSize.y) / 2;
        return sf::Vector2f(x, y);
    }

    if (totalPanels == 2) {
        float x = (index == 0) ? 0 : WINDOW_WIDTH / 2;
        float y = (WINDOW_HEIGHT - panelSize.y) / 2;
        return sf::Vector2f(x, y);
    }

    if (totalPanels == 3) {
        if (index < 2) {
            float x = (index == 0) ? 0 : WINDOW_WIDTH / 2;
            float y = 120;
            return sf::Vector2f(x, y);
        } else {
            float x = 0;
            float y = 120 + panelSize.y;
            return sf::Vector2f(x, y);
        }
    }

    // totalPanels == 4
    int row = index / 2;
    int col = index % 2;
    float x = col * panelSize.x;
    float y = 120 + row * panelSize.y;
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
        sf::Vector2f panelSize;

        switch (algorithms.size()) {
            case 1:
                panelSize = sf::Vector2f(WINDOW_WIDTH * 0.8f, WINDOW_HEIGHT * 0.6f);
                break;
            case 2:
                panelSize = sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT * 0.6f);
                break;
            case 3:
                panelSize = (i < 2) 
                    ? sf::Vector2f(WINDOW_WIDTH / 2.0f, (WINDOW_HEIGHT - 150) / 2.0f)
                    : sf::Vector2f(WINDOW_WIDTH, (WINDOW_HEIGHT - 150) / 2.0f);
                break;
            case 4:
                panelSize = sf::Vector2f(WINDOW_WIDTH / 2.0f, (WINDOW_HEIGHT - 150) / 2.0f);
                break;
            default:
                panelSize = sf::Vector2f(400, 300); // fallback
                break;
        }

        sf::Vector2f position = calculatePanelPosition(i, algorithms.size(), panelSize);
        
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



