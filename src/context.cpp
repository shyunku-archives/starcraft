#include "context.hpp"
#include "submodules/util.hpp"
#include "environments.hpp"
#include <iostream>
#include <format>

Context::Context(sf::RenderWindow* window) {
	this->window = window;
	this->assetTracker = Asset::Tracker();
	this->gameStateManager = GameStateManager();
	this->startLocalTime = getCurrentTime();
	this->lastRenderTime = getCurrentTime();
	this->ddd = getCurrentTime();

	this->update();
}

void Context::update() {
	this->currentDimension = Dimension(this->window->getSize().x, this->window->getSize().y);
	this->currentTime = getCurrentTime();
	this->currentLocalTime = getCurrentTime() - this->startLocalTime;
	this->deltaTime = this->currentTime - this->lastRenderTime;
	this->lastRenderTime = this->currentTime;
	this->frameRate = 1 / this->deltaTime;

	if (this->currentLocalTime - this->ddd > 3) {
		this->ddd = this->currentLocalTime;
		this->pushLog(format("[Context] Updated: {}, size: {}", this->currentLocalTime, this->logs.size()));
	}
}

void Context::pushLog(string log) {
	this->logs.push_back(log);
	if (this->logs.size() > GlobalLogger::MAX_STACK_SIZE) {
		this->logs.pop_front();
	}
}