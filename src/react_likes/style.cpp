#include "style.hpp"

CompleteStyle::CompleteStyle() {
	this->display = LayoutType::Flex;
	this->flex = 1;
	this->flexDirection = FlexDirection::Row;
	this->justifyContent = JustifyContent::Start;
	this->alignItems = AlignItems::Start;
	this->width = 0;
	this->height = 0;
	this->margin = Cardinal(0, 0, 0, 0);
	this->padding = Cardinal(0, 0, 0, 0);
	this->absolute = Cardinal(0, 0, 0, 0);
	this->backgroundColor = sf::Color::Transparent;
	this->borderColor = sf::Color::Transparent;
	this->borderWidth = 0;
	this->text = "";
	this->font = Asset::Font::InGameFont;
	this->fontSize = 16.0;
	this->color = sf::Color::Black;
}

const CompleteStyle Style::Default = CompleteStyle();


Style::Style() {}

Style::~Style() {}

Style::Style(const Style& other) {
	this->_display = make_unique<LayoutType>(other._display ? new LayoutType(*other._display) : nullptr);
	this->_flex = make_unique<double>(other._flex ? new double(*other._flex) : nullptr);
	this->_flexDirection = make_unique<FlexDirection>(other._flexDirection ? new FlexDirection(*other._flexDirection) : nullptr);
	this->_justifyContent = make_unique<JustifyContent>(other._justifyContent ? new JustifyContent(*other._justifyContent) : nullptr);
	this->_alignItems = make_unique<AlignItems>(other._alignItems ? new AlignItems(*other._alignItems) : nullptr);
	this->_width = make_unique<double>(other._width ? new double(*other._width) : nullptr);
	this->_height = make_unique<double>(other._height ? new double(*other._height) : nullptr);
	this->_margin = make_unique<Cardinal>(other._margin ? new Cardinal(*other._margin) : nullptr);
	this->_padding = make_unique<Cardinal>(other._padding ? new Cardinal(*other._padding) : nullptr);
	this->_absolute = make_unique<Cardinal>(other._absolute ? new Cardinal(*other._absolute) : nullptr);
	this->_backgroundColor = make_unique<sf::Color>(other._backgroundColor ? new sf::Color(*other._backgroundColor) : nullptr);
	this->_borderColor = make_unique<sf::Color>(other._borderColor ? new sf::Color(*other._borderColor) : nullptr);
	this->_borderWidth = make_unique<double>(other._borderWidth ? new double(*other._borderWidth) : nullptr);
	this->_text = make_unique<string>(other._text ? new string(*other._text) : nullptr);
	this->_font = make_unique<Asset::Font>(other._font ? new Asset::Font(*other._font) : nullptr);
	this->_fontSize = make_unique<double>(other._fontSize ? new double(*other._fontSize) : nullptr);
	this->_color = make_unique<sf::Color>(other._color ? new sf::Color(*other._color) : nullptr);
}

CompleteStyle Style::overwriteWithDefault() {
	Style copied(*this);
	CompleteStyle style = CompleteStyle();
	if (copied._display != nullptr) style.display = Style::Default.display;
	if (copied._flex != nullptr) style.flex = Style::Default.flex;
	if (copied._flexDirection != nullptr) style.flexDirection = Style::Default.flexDirection;
	if (copied._justifyContent != nullptr) style.justifyContent = Style::Default.justifyContent;
	if (copied._alignItems != nullptr) style.alignItems = Style::Default.alignItems;
	if (copied._width != nullptr) style.width = Style::Default.width;
	if (copied._height != nullptr) style.height = Style::Default.height;
	if (copied._margin != nullptr) style.margin = Style::Default.margin;
	if (copied._padding != nullptr) style.padding = Style::Default.padding;
	if (copied._absolute != nullptr) style.absolute = Style::Default.absolute;
	if (copied._backgroundColor != nullptr) style.backgroundColor = Style::Default.backgroundColor;
	if (copied._borderColor != nullptr) style.borderColor = Style::Default.borderColor;
	if (copied._borderWidth != nullptr) style.borderWidth = Style::Default.borderWidth;
	if (copied._text != nullptr) style.text = Style::Default.text;
	if (copied._font != nullptr) style.font = Style::Default.font;
	if (copied._fontSize != nullptr) style.fontSize = Style::Default.fontSize;
	if (copied._color != nullptr) style.color = Style::Default.color;
	return style;
}

Style Style::display(LayoutType value) {
	this->_display = make_unique<LayoutType>(&value);
	return *this;
}

Style Style::flex(double value) {
	this->_flex = make_unique<double>(&value);
	return *this;
}

Style Style::flexDirection(FlexDirection value) {
	this->_flexDirection = make_unique<FlexDirection>(&value);
	return *this;
}

Style Style::justifyContent(JustifyContent value) {
	this->_justifyContent = make_unique<JustifyContent>(&value);
	return *this;
}

Style Style::alignItems(AlignItems value) {
	this->_alignItems = make_unique<AlignItems>(&value);
	return *this;
}

Style Style::width(double value) {
	this->_width = make_unique<double>(&value);
	return *this;
}

Style Style::height(double value) {
	this->_height = make_unique<double>(&value);
	return *this;
}

Style Style::margin(Cardinal value) {
	this->_margin = make_unique<Cardinal>(&value);
	return *this;
}

Style Style::padding(Cardinal value) {
	this->_padding = make_unique<Cardinal>(&value);
	return *this;
}

Style Style::absolute(Cardinal value) {
	this->_absolute = make_unique<Cardinal>(&value);
	return *this;
}

Style Style::backgroundColor(sf::Color value) {
	this->_backgroundColor = make_unique<sf::Color>(&value);
	return *this;
}

Style Style::borderColor(sf::Color value) {
	this->_borderColor = make_unique<sf::Color>(&value);
	return *this;
}

Style Style::borderWidth(double value) {
	this->_borderWidth = make_unique<double>(&value);
	return *this;
}

Style Style::text(string value) {
	this->_text = make_unique<string>(&value);
	return *this;
}

Style Style::font(Asset::Font value) {
	this->_font = make_unique<Asset::Font>(&value);
	return *this;
}

Style Style::fontSize(double value) {
	this->_fontSize = make_unique<double>(&value);
	return *this;
}

Style Style::color(sf::Color value) {
	this->_color = make_unique<sf::Color>(&value);
	return *this;
}