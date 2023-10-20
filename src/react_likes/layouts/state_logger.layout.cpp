#include "../layouts.hpp"
#include "molecules/text.layout.cpp"
#include <format>
#include <deque>

struct StateLoggerState {
	double fps;
	double dt;
};

class StateLoggerLayout : public Layout<StateLoggerState> {
private:
	double fps;
	double dt;
public:
	StateLoggerLayout() : Layout() {
		this->style.display(LayoutType::Flex);
		this->style.flexDirection(FlexDirection::Column);
		this->style.width(500);
		this->style.absolute(Cardinal(50, 50, 50, 0));
		this->style.backgroundColor(sf::Color(0, 0, 0, 255));
		this->style.color(sf::Color::White);
	}

	bool shouldRepaint(StateLoggerState p) override {
		//return fps != p.fps || dt != p.dt;
		return true;
	}

	Model buildModel() {
		// get rendered logs with subordinate layouts
		Model model;
		model.set("fps", TextBox(format("fps: {}", fps)));
		model.set("dt", TextBox(format("dt: {}", dt)));
		return model;
	}
};