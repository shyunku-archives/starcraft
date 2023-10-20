#pragma once
#include <stack>
#include <SFML/Graphics.hpp>

class Contextful;
class Context;

class GameState {
public:
    GameState() {};
    virtual void init(Context* ctx) {};
    virtual void destroy() {};
    virtual void onWindowResize(sf::RenderWindow& window) {};
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

