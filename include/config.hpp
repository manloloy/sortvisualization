#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics.hpp>

// Global font (must be defined in exactly one .cpp)
extern sf::Font globalFont;

// UI and Style Constants
const sf::Color BG_COLOR = sf::Color(30, 30, 30);
const sf::Color SORTED_COLOR = sf::Color::Green;
const sf::Color ACTIVE_COLOR = sf::Color::Red;
const sf::Color DEFAULT_COLOR = sf::Color::White;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;
const int NUM_BARS = 25;
const int BAR_WIDTH = 20;

#endif
