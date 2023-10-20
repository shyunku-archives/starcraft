#pragma once
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "submodules/types.hpp"

using namespace std;

namespace Asset {
	enum SoundTrack {
		NullSoundTrack = 0,
		MenuScreenBackgroundMusic,
	};

	enum Image {
		NullImage = 10000,
		MenuScreenBackgroundImage,
	};

	enum Font {
		NullFont = 20000,
		TitleFont,
		InGameFont,
	};

	class Tracker {
	private:
		static string getPath(int id);
		static void bindPath(int id, string path);
	public:
		static unordered_map<int, string> paths;
		// caches
		static unordered_map<int, sf::Font> cached_fonts;

		Tracker();
		// TODO :: add caching?
		static sf::Music* loadSound(int id);
		static pair<sf::Sprite, shared_ptr<sf::Texture>> loadImage(int id);
		static pair<sf::Sprite, shared_ptr<sf::Texture>> loadImage(int id, sf::IntRect rect);
		static pair<sf::Sprite, shared_ptr<sf::Texture>> loadImage(int id, Bounds bounds);
		static sf::Font loadFont(int id);
	};
}