#include "AppManager.hpp"
#include "config.hpp"
#include <iostream>

// Define the global font here
sf::Font globalFont;

int main() {
    if (!globalFont.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Failed to load font from assets/arial.ttf\n";
        return 1;
    }

    AppManager::getInstance().run();
    return 0;
}
