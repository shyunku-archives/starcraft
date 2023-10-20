#include "../layouts.hpp"
#include "molecules/text.layout.cpp"
#include <deque>

struct GlobalLoggerState {
	deque<string> logs;
};

class GlobalLoggerLayout : public Layout<GlobalLoggerState> {
private:
	deque<string>* _logs;
public:
	GlobalLoggerLayout() : Layout() {
		this->style.display(LayoutType::Flex);
		this->style.flexDirection(FlexDirection::Column);
		this->style.width(500);
		this->style.absolute(Cardinal(50, 50, 50, 0));
		this->style.backgroundColor(sf::Color(0, 0, 0, 255));
		this->style.color(sf::Color::White);
	}

	bool shouldRepaint() {
		return true;
	}

	Model buildModel() {
		// get rendered logs with subordinate layouts
		Model model;
		model.set("logs", *_logs);
		return model;
	}
};