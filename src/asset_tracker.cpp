#include <format>
#include "asset_tracker.hpp"
#include "submodules/starcraft_exception.hpp"

namespace Asset {
	unordered_map<int, string> Asset::Tracker::paths;
	unordered_map<int, sf::Font> Asset::Tracker::cached_fonts;

	Tracker::Tracker() {
		// Soundtracks
		bindPath(SoundTrack::MenuScreenBackgroundMusic, "assets/sounds/main_menu_soundtrack.mp3");

		// Images
		bindPath(Image::NullImage, "assets/images/null.png");
		bindPath(Image::MenuScreenBackgroundImage, "assets/images/main_menu_background.png");

		// Fonts
		bindPath(Font::TitleFont, "assets/fonts/title_font.ttf");
		bindPath(Font::InGameFont, "assets/fonts/in_game_font.ttf");
	}

	string Tracker::getPath(int id) {
		if (paths.find(id) == paths.end()) {
			throw StarcraftException(format("Asset not found: {}", id));
		}
		return paths.find(id)->second;
	}

	void Tracker::bindPath(int id, string path) {
		paths.insert(make_pair(id, path));
	}

	sf::Music* Tracker::loadSound(int id) {
		string path = Tracker::getPath(id);
		sf::Music* music = new sf::Music();
		bool success = music->openFromFile(path);
		if (!success) {
			throw StarcraftException(format("Failed to load sound file: {}", path));
		}
		return music;
	}

	pair<sf::Sprite, shared_ptr<sf::Texture>> Tracker::loadImage(int id) {
		string path = Tracker::getPath(id);
		auto texture = make_shared<sf::Texture>();
		bool success = texture.get()->loadFromFile(path);
		if (!success) {
			throw StarcraftException(format("Failed to load image file: {}", path));
		}

		sf::Sprite sprite = sf::Sprite();
		sprite.setTexture(*texture.get());
		return make_pair(sprite, texture);
	}

	pair<sf::Sprite, shared_ptr<sf::Texture>> Tracker::loadImage(int id, sf::IntRect rect) {
		string path = Tracker::getPath(id);
		auto texture = make_shared<sf::Texture>();
		bool success = texture.get()->loadFromFile(path, rect);
		if (!success) {
			throw StarcraftException(format("Failed to load image file: {}", path));
		}

		sf::Sprite sprite = sf::Sprite();
		sprite.setTexture(*texture.get());
		return make_pair(sprite, texture);
	}

	pair<sf::Sprite, shared_ptr<sf::Texture>> Tracker::loadImage(int id, Bounds bounds) {
		string path = Tracker::getPath(id);
		auto texture = make_shared<sf::Texture>();
		bool success = texture.get()->loadFromFile(path);
		if (!success) {
			throw StarcraftException(format("Failed to load image file: {}", path));
		}

		sf::Vector2u size = texture.get()->getSize();
		float scaleX = (float)bounds.w / (float)size.x;
		float scaleY = (float)bounds.h / (float)size.y;

		sf::Sprite sprite = sf::Sprite();
		sprite.setTexture(*texture.get());
		sprite.setScale(scaleX, scaleY);

		return make_pair(sprite, texture);
	}

	sf::Font Tracker::loadFont(int id) {
		if (Tracker::cached_fonts.find(id) != Tracker::cached_fonts.end()) {
			return Tracker::cached_fonts.at(id);
		}
		string path = Tracker::getPath(id);
		sf::Font font;
		bool success = font.loadFromFile(path);
		if (!success) {
			throw StarcraftException(format("Failed to load font file: {}", "assets/fonts/null.ttf"));
		}
		Tracker::cached_fonts.insert(make_pair(id, font));
		return font;
	}
}