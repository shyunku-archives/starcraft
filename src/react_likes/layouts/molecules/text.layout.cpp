#include "../../layouts.hpp"

class TextBox : public Layout<string> {
public:
	TextBox(string text) : Layout(false) {
		this->style.display(LayoutType::Flex);
		this->style.justifyContent(JustifyContent::Start);
		this->style.alignItems(AlignItems::Center);
		this->style.text(text);
		this->style.color(sf::Color::White);
		this->style.height(25);
	}
};