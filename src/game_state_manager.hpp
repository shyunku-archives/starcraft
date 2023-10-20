#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include "asset_tracker.hpp"

class GameState;
class Context;

class GameStateManager {
protected:
    std::stack<GameState*> states;

public:
    GameStateManager();
    void pushState(Context* ctx, GameState* state);
    void popState();
    GameState* currentState();
};