#include <SFML/Audio.hpp>
#include "../context.hpp"
#include "../game_state.hpp"
#include "../react_likes/layouts.hpp"
#include <iostream>

class MenuState : public GameState {
private:
	sf::Music* backgroundMusic;
	pair<sf::Sprite, shared_ptr<sf::Texture>> backgroundImage;
public:
	MenuState() : GameState() {
		this->backgroundMusic = nullptr;
	}
	void init(Context* ctx) override {
		this->backgroundMusic = ctx->assetTracker.loadSound(Asset::SoundTrack::MenuScreenBackgroundMusic);
		this->backgroundMusic->play();

		this->backgroundImage = ctx->assetTracker.loadImage(Asset::Image::MenuScreenBackgroundImage,
			Bounds(ctx->currentDimension.w, ctx->currentDimension.h));
	}
	void destroy() override {
		this->backgroundMusic->stop();
		delete this->backgroundMusic; // TODO :: delete if caching is implemented
		delete this->backgroundImage.second.get();
	}
	void handleInput() override {

	}
	void update() override {

	}
	void draw(sf::RenderWindow& window) override {
		// background
		window.draw(this->backgroundImage.first);

		/*Layout().height(1000).id(0).children(
			Layout().backgroundColor(sf::Color::Red).id(1),
			Layout().backgroundColor(sf::Color::Green).id(2).width(30),
			Layout().backgroundColor(sf::Color::Blue).id(3).flex(2).borderWidth(10),
			Layout(
				Layout().backgroundColor(sf::Color::Cyan).id(5),
				Layout().backgroundColor(sf::Color::Black).id(7).height(80),
				Layout().backgroundColor(sf::Color::Magenta).id(6).flex(2)
			).flexDirection(FlexDirection::Column).backgroundColor(sf::Color::Yellow).id(4).flex(1),
			Layout().display(LayoutType::Fixed).id(8).width(100).height(200).backgroundColor(sf::Color::Yellow)
			.absolute(Cardinal().top(100).left(300))
		).build(window);*/
	}
};