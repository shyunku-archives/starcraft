#include "render_view_state.hpp"

RenderViewState::RenderViewState() {
	this->renderTexture = new sf::RenderTexture();
	this->bounds = Bounds(0, 0, 0, 0);
}

void RenderViewState::setBounds(Bounds _bounds) {
	this->bounds = _bounds;
	this->renderTexture->create(bounds.w, bounds.h);
}

void RenderViewState::updateTexture(sf::RenderTexture* texture) {
	this->renderTexture->clear(sf::Color::Transparent);
	this->renderTexture->draw(sf::Sprite(texture->getTexture()));
}

sf::Sprite RenderViewState::getSprite() const {
	sf::Sprite spirte(renderTexture->getTexture());
	spirte.setPosition(bounds.x, bounds.y);
	return spirte;
}