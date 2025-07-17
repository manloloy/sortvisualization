#ifndef SORT_RUSH_SCREEN_HPP
#define SORT_RUSH_SCREEN_HPP

#include "Screen.hpp"
#include "FallingBlock.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

class SortRushScreen : public Screen {
public:
    SortRushScreen();
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    std::vector<FallingBlock> blocks;
    float spawnTimer = 0.0f;
    float spawnInterval = 1.f; // seconds between new block spawns
};

#endif
