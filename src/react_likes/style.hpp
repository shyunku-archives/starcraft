#pragma once
#include "../submodules/types.hpp"
#include "../asset_tracker.hpp"
#include <SFML/Graphics.hpp>

enum class LayoutType {
	Flex, // act like a flexbox
	Fixed, // arranged by ancestor layout
};

enum class FlexDirection {
	Row,
	Column,
};

enum class JustifyContent {
	Start,
	End,
	Center,
};

enum class AlignItems {
	Start,
	End,
	Center,
};

struct CompleteStyle {
	CompleteStyle();

	LayoutType display;

	double flex;
	FlexDirection flexDirection;
	JustifyContent justifyContent;
	AlignItems alignItems;

	double width;
	double height;

	Cardinal margin;
	Cardinal padding;
	Cardinal absolute;

	sf::Color backgroundColor;
	sf::Color borderColor;
	double borderWidth;

	string text;
	Asset::Font font;
	double fontSize;
	sf::Color color;
};

class Style {
public:
	static const CompleteStyle Default;

	unique_ptr<LayoutType> 		_display;

	unique_ptr<double>			_flex;
	unique_ptr<FlexDirection>	_flexDirection;
	unique_ptr<JustifyContent>	_justifyContent;
	unique_ptr<AlignItems>		_alignItems;

	unique_ptr<double>			_width;
	unique_ptr<double>			_height;

	unique_ptr<Cardinal>		_margin;
	unique_ptr<Cardinal>		_padding;
	unique_ptr<Cardinal>		_absolute;

	unique_ptr<sf::Color>		_backgroundColor;
	unique_ptr<sf::Color>		_borderColor;
	unique_ptr<double>			_borderWidth;

	unique_ptr<string>			_text;
	unique_ptr<Asset::Font>		_font;
	unique_ptr<double>			_fontSize;
	unique_ptr<sf::Color>		_color;

	Style();
	~Style();
	Style(const Style& other);
	CompleteStyle overwriteWithDefault();

	Style display(LayoutType value);
	Style flex(double value);
	Style flexDirection(FlexDirection value);
	Style justifyContent(JustifyContent value);
	Style alignItems(AlignItems value);
	Style width(double value);
	Style height(double value);
	Style margin(Cardinal value);
	Style padding(Cardinal value);
	Style absolute(Cardinal value);
	Style backgroundColor(sf::Color value);
	Style borderColor(sf::Color value);
	Style borderWidth(double value);
	Style text(string value);
	Style font(Asset::Font value);
	Style fontSize(double value);
	Style color(sf::Color value);
};