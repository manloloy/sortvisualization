// AppManager.hpp
#ifndef APP_MANAGER_HPP
#define APP_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "Screen.hpp"

class AppManager {
public:
    static AppManager& getInstance();

    void run();

    void pushScreen(std::unique_ptr<Screen> screen);
    void popScreen();
    void returnToMenu();
    sf::RenderWindow& getWindow();


private:
    AppManager(); // private constructor

    sf::RenderWindow window;
    std::stack<std::unique_ptr<Screen>> screenStack;
    bool shouldReturnToMenu = false;

};

#endif // APP_MANAGER_HPP
