#pragma once
#include <SFML/Graphics.hpp>
#include "../submodules/types.hpp"

class RenderViewState {
private:
	sf::RenderTexture* renderTexture;
	Bounds bounds;

public:
	RenderViewState();
	void setBounds(Bounds _bounds);
	void updateTexture(sf::RenderTexture* texture);
	sf::Sprite getSprite() const;
};