//#include "layouts.hpp"
//#include <iostream>
//#include <format>
//
//template <typename StateType>
//Layout<StateType>::Layout() {
//	this->renderViewState = RenderViewState();
//	this->_id = -1; // TODO :: set incremental id (or random)
//	this->_cachedModel = nullptr;
//	this->needsRepaint = true;
//}
//
//
//Layout Layout::id(unsigned long long value) {
//	this->_id = value;
//	return *this;
//}
//
//vector<RenderViewState> Layout::getFlattenedRenderViewStates() {
//	vector<RenderViewState> result;
//	result.push_back(this->renderViewState);
//
//	LayoutNode currentNode = this->model();
//	for (LayoutNode childLayoutNode : currentNode.children) {
//		Layout child = *childLayoutNode.layout;
//		vector<RenderViewState> childFlattened = child.getFlattenedRenderViewStates();
//		result.insert(result.end(), childFlattened.begin(), childFlattened.end());
//	}
//	return result;
//}
//
//Bounds Layout::calcBounds(CompleteStyle myStyle, Bounds parentBound) {
//	// TODO :: set null to all properties as default & set default values while building
//	// TODO :: maybe with caching? (for optimization)
//
//	double winWidth = parentBound.w;
//	double winHeight = parentBound.h;
//	double width = myStyle.width > 0 ? myStyle.width : winWidth;
//	double height = myStyle.height > 0 ? myStyle.height : winHeight;
//	Bounds bounds;
//
//	switch (myStyle.display) {
//	case LayoutType::Flex:
//		bounds = Bounds(0, 0, width, height);
//		break;
//	case LayoutType::Fixed:
//		bounds = Bounds(
//			myStyle.absolute._left > 0 ? myStyle.absolute._left : (
//				myStyle.width > 0 ? winWidth - myStyle.width - myStyle.absolute._right : 0
//				),
//			myStyle.absolute._top > 0 ? myStyle.absolute._top : (
//				myStyle.height > 0 ? winHeight - myStyle.height - myStyle.absolute._bottom : 0
//				),
//			myStyle.width > 0 ? myStyle.width : winWidth - myStyle.absolute._left - myStyle.absolute._right,
//			myStyle.height > 0 ? myStyle.height : winHeight - myStyle.absolute._top - myStyle.absolute._bottom
//		);
//		break;
//	}
//
//	return bounds;
//}
//
//CompleteStyle Layout::calcStyle(CompleteStyle parentStyle) {
//	// TODO:: overwrite specfic styles with parent style
//	return this->style.overwriteWithDefault();
//}
//
//void Layout::repainted(sf::RenderTexture* texture) {
//	this->renderViewState.updateTexture(texture);
//	this->needsRepaint = false;
//}
//
//LayoutNode Layout::model() {
//	if (this->_cachedModel != nullptr) {
//		this->_cachedModel = &this->buildModel();
//	}
//}
//
//template <typename Props>
//bool Layout::shouldRepaint(Props p) {
//	static_assert(is_base_of<Style, Props>::value, "Props must be a subclass of Style");
//	// as default, compare all properties of next style with previous style
//	CompleteStyle currentCompiledStyle = this->calcStyle(this->style);
//	CompleteStyle nextCompiledStyle = this->calcStyle(p);
//	if (currentCompiledStyle != nextCompiledStyle) return true;
//	return false;
//}
//
//void Layout::updateCheck() {
//	// check should repaint & mark as needs repaint
//	if(this->shouldRepaint(this->style)) this->needsRepaint = true;
//
//	LayoutNode currentNode = this->model();
//	for (LayoutNode childLayoutNode : currentNode.children) {
//		Layout* childLayout = childLayoutNode.layout;
//		childLayout->updateCheck();
//	}
//}
//
//RenderViewState Layout::lastPainting() {
//	return this->renderViewState;
//}
//
//void Layout::render(sf::RenderWindow& window) {
//	vector<RenderViewState> flattenLayers = this->getFlattenedRenderViewStates();
//	// TODO :: apply z-index
//	for (RenderViewState layer : flattenLayers) {
//		sf::Sprite sprite = layer.getSprite();
//		window.draw(sprite);
//	}
//}
//
//// parentBound indicates the maximum bounds of this layout
//void Layout::repaint(CompleteStyle parentStyle, Bounds parentBound) {
//	if(!this->needsRepaint) return;
//
//	// overwrite this style with default
//	CompleteStyle style = this->calcStyle(parentStyle);
//
//	// calculate bounds
//	Bounds bounds = this->calcBounds(style, parentBound);
//
//	// create render texture
//	sf::RenderTexture* renderTexture = new sf::RenderTexture();
//	renderTexture->create(parentBound.w, parentBound.h);
//
//	// draw self
//	this->build(*renderTexture, style, bounds);
//
//	// draw children (calculate subordinates layout)
//	vector<Layout> childrens;
//	LayoutNode currentNode = this->model();
//	for (LayoutNode childLayoutNode : currentNode.children) {
//		Layout* childLayout = childLayoutNode.layout;
//		childrens.push_back(*childLayout);
//	}
//
//	bool isRow = style.flexDirection == FlexDirection::Row;
//	double totalFlex = 0;
//	double totalWidth = 0;
//	double totalHeight = 0;
//	for (Layout child : childrens) {
//		CompleteStyle childStyle = child.calcStyle(style);
//		// TODO :: consider caching style (for optimization)
//		if (childStyle.display == LayoutType::Fixed) continue;
//		if (isRow) {
//			if (childStyle.width > 0) totalWidth += childStyle.width;
//			else totalFlex += childStyle.flex;
//			totalHeight = std::max(totalHeight, childStyle.height);
//		}
//		else {
//			if (childStyle.height > 0) totalHeight += childStyle.height;
//			else totalFlex += childStyle.flex;
//			totalWidth = std::max(totalWidth, childStyle.width);
//		}
//	}
//
//	double remainingSpace = isRow ? bounds.w - totalWidth : bounds.h - totalHeight;
//	double unitFlexSpace = totalFlex > 0 ? remainingSpace / totalFlex : 0;
//
//	double curX = bounds.x;
//	double curY = bounds.y;
//
//	//cout << format("totalFlex: {}, remainingSpace: {}, unitFlexSpace: {}",
//	//	totalFlex, remainingSpace, unitFlexSpace) << endl;
//
//	for (Layout child : childrens) {
//		CompleteStyle childStyle = child.calcStyle(style);
//		switch (childStyle.display) {
//		case LayoutType::Flex:
//			if (isRow) {
//				double width = childStyle.width;
//				if (width == 0) width = unitFlexSpace * childStyle.flex;
//				if (width < 0) width = 0;
//				child.repaint(style, Bounds(curX, bounds.y, width, bounds.h));
//				curX += width;
//			}
//			else {
//				double height = childStyle.height;
//				if (height == 0) height = unitFlexSpace * childStyle.flex;
//				if (height < 0) height = 0;
//				child.repaint(style, Bounds(bounds.x, curY, bounds.w, height));
//				curY += height;
//			}
//			break;
//		case LayoutType::Fixed:
//			child.repaint(style, Bounds(0, 0, 0, 0));
//			break;
//		}
//	}
//
//	// save render texture to render view state
//	this->renderViewState.updateTexture(renderTexture);
//}
//
//void Layout::build(sf::RenderTexture& view, CompleteStyle style, Bounds bounds) {
//	//cout << format("[Layout#{}] x: {}, y: {}, w: {}, h: {}, children: {}, text: \"{}...\"", 
//	//	style.id, bounds.x, bounds.y, bounds.w, bounds.h, style.children.size(), style.text.substr(0, 8)) << endl;
//	//if (style.display == LayoutType::Fixed) {
//	//	cout << format("\tabsolute: top: {}, right: {}, bottom: {}, left: {}", 
//	//		style.absolute._top, style.absolute._right, style.absolute._bottom, style.absolute._left) << endl;
//	//}
//
//	// ignore drawing self if width or height is under 0
//	if (bounds.w > 0 && bounds.h > 0) {
//		// consider border width
//		double x = bounds.x + style.borderWidth;
//		double y = bounds.y + style.borderWidth;
//		double w = bounds.w - style.borderWidth * 2;
//		double h = bounds.h - style.borderWidth * 2;
//
//		sf::RectangleShape shape;
//		shape.setPosition(x, y);
//		shape.setSize(sf::Vector2f(float(w), float(h)));
//		shape.setFillColor(style.backgroundColor);
//		shape.setOutlineColor(style.borderColor);
//		shape.setOutlineThickness(style.borderWidth);
//		view.draw(shape);
//	}
//
//	// draw text if exists
//	if (!style.text.empty()) {
//		sf::Font font = Asset::Tracker::loadFont(style.font);
//		sf::Text text;
//		text.setString(style.text);
//		text.setFont(font);
//		text.setCharacterSize(style.fontSize);
//		text.setFillColor(style.color);
//
//		// apply justify content & align items as text alignment
//		double tx = bounds.x + style.padding._left;
//		double ty = bounds.y + style.padding._top;
//		switch (style.justifyContent) { // horizontal
//			case JustifyContent::Start:
//				break;
//			case JustifyContent::Center:
//				tx += bounds.w / 2 - text.getLocalBounds().width / 2;
//				break;
//			case JustifyContent::End:
//				tx += bounds.w - text.getLocalBounds().width;
//				break;
//		}
//		switch (style.alignItems) { // vertical
//			case AlignItems::Start:
//				break;
//			case AlignItems::Center:
//				ty += bounds.h / 2 - text.getLocalBounds().height / 2;
//				break;
//			case AlignItems::End:
//				ty += bounds.h - text.getLocalBounds().height;
//				break;
//		}
//		text.setPosition(tx, ty);
//
//		// TODO :: clip (overflow)
//		//sf::View originalView = window.getView();
//		//sf::View clipView(sf::FloatRect(x, y, w, h));
//		//window.setView(clipView);
//		view.draw(text);
//		//window.setView(originalView);
//
//		//cout << format("Text drawing: x: {}, y: {}, w: {}, h: {}", tx, ty, text.getLocalBounds().width, text.getLocalBounds().height) << endl;
//	}
//}
//
////Layout Layout::children(vector<Layout> value) {
////	this->_children = value;
////	return *this;
////}