#include "game_state_manager.hpp"
#include "game_state.hpp"
#include "context.hpp"

class GameState;

GameStateManager::GameStateManager() {}

void GameStateManager::pushState(Context* ctx, GameState* state) {
    states.push(state);
    state->init(ctx);
}

void GameStateManager::popState() {
    if (states.empty()) return;
    GameState* state = states.top();
    state->destroy();
    delete state;
    states.pop();
}

GameState* GameStateManager::currentState() {
    if (states.empty()) return nullptr;
    return states.top();
}