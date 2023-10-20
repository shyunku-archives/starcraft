#pragma once
#include "asset_tracker.hpp"
#include "game_state_manager.hpp"
#include "submodules/types.hpp"
#include <queue>

class GameStateManager;

class Context {
private:
	double lastRenderTime;
	double ddd; // TODO :: delete
public:
	sf::RenderWindow* window;
	Asset::Tracker assetTracker;
	GameStateManager gameStateManager;

	double startLocalTime;

	Dimension currentDimension;
	double currentTime;
	double currentLocalTime;
	double deltaTime;
	double frameRate;

	// logs
	std::deque<string> logs;

	Context(sf::RenderWindow* window);
	void update();
	void pushLog(string log);
};