// AppManager.cpp
#include "AppManager.hpp"
#include "SelectionScreen.hpp"

AppManager::AppManager()
    : window(sf::VideoMode(1000, 800), "Sorting Visualizer") {
    window.setFramerateLimit(60);
}

AppManager& AppManager::getInstance() {
    static AppManager instance;
    return instance;
}

void AppManager::run() {
    pushScreen(std::make_unique<SelectionScreen>()); // start at main menu

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!screenStack.empty())
                screenStack.top()->handleEvent(event);
        }

        if (!screenStack.empty())
            screenStack.top()->update(dt);

        window.clear(sf::Color::Black);

        if (!screenStack.empty())
            screenStack.top()->draw(window);

        window.display();

        if (shouldReturnToMenu) {
            while (!screenStack.empty())
                screenStack.pop();
            pushScreen(std::make_unique<SelectionScreen>());
            shouldReturnToMenu = false;
        }

    }
}

void AppManager::pushScreen(std::unique_ptr<Screen> screen) {
    screenStack.push(std::move(screen));
}

void AppManager::popScreen() {
    if (!screenStack.empty())
        screenStack.pop();
}

void AppManager::returnToMenu() {
    shouldReturnToMenu = true;
}


sf::RenderWindow& AppManager::getWindow() {
    return window;
}