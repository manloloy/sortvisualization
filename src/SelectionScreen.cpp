// src/SelectionScreen.cpp
#include "SelectionScreen.hpp"
#include "AppManager.hpp"
#include "SortScreen.hpp"
#include "config.hpp"

SelectionScreen::SelectionScreen()
    : startButton("Start Sorting", {100, 400}, {200, 60})
{
    prompt.setFont(globalFont);
    prompt.setString("Select algorithms to visualize:");
    prompt.setCharacterSize(24);
    prompt.setPosition(100, 80);
    prompt.setFillColor(sf::Color::White);

    // Create algorithm buttons
    const std::vector<std::string> algoNames = {
        "Selection Sort", "Insertion Sort", "Quick Sort", "Merge Sort"
    };

    for (size_t i = 0; i < algoNames.size(); ++i) {
        float x = 100.0f;
        float y = 140.0f + i * 60.0f;

        Button btn(algoNames[i], {x, y}, {200, 50});

        // Default to not selected
        algoSelected.push_back(false);

        // Add toggle logic with capture-by-reference [i]
        btn.setCallback([this, i]() {
            algoSelected[i] = !algoSelected[i];
        });

        algoButtons.push_back(std::move(btn));
    }

    startButton.setCallback([this]() {
        selectedAlgos.clear();

        const std::vector<SortAlgorithm> allAlgos = {
            SortAlgorithm::Selection,
            SortAlgorithm::Insertion,
            SortAlgorithm::Quick,
            SortAlgorithm::Merge
        };

        for (size_t i = 0; i < algoSelected.size(); ++i) {
            if (algoSelected[i]) {
                selectedAlgos.push_back(allAlgos[i]);
            }
        }

        if (!selectedAlgos.empty()) {
            AppManager::getInstance().pushScreen(
                std::make_unique<SortScreen>(selectedAlgos)
            );
        }
    });
}

void SelectionScreen::handleEvent(const sf::Event& event) {
    auto& window = AppManager::getInstance().getWindow();

    for (auto& button : algoButtons)
        button.handleEvent(event, window);

    startButton.handleEvent(event, window);
}

void SelectionScreen::update(float) {
    // nothing to update yet
}

void SelectionScreen::draw(sf::RenderWindow& window) {
    window.clear(BG_COLOR);
    window.draw(prompt);

    for (size_t i = 0; i < algoButtons.size(); ++i) {
        // Visually toggle button color
        if (algoSelected[i])
            algoButtons[i].draw(window); // default color
        else {
            // draw with grayed out style
            sf::RectangleShape rect = algoButtons[i].getShape();
            sf::Text label = algoButtons[i].getLabel();

            rect.setFillColor(sf::Color(50, 50, 50)); // darker
            window.draw(rect);
            window.draw(label);
            continue;
        }

        algoButtons[i].draw(window);
    }

    startButton.draw(window);
}
