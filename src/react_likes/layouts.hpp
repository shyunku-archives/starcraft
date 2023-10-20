#pragma once
#include "render_view_state.hpp"
#include "style.hpp"
#include <boost/variant.hpp>
#include <boost/any.hpp>
#include <boost/optional.hpp>
#include <vector>

using namespace std;

typedef SequencedHashMap<string, Layout<boost::any>> Model;

//class Model {
//public:
//	SequencedHashMap<string, boost::variant<boost::any>> children;
//};

template <typename StateType>
class Layout {
private:
	StateType state;
	//LayoutNode* _cachedModel;
	RenderViewState captured; //  delete?
	Model* _model;
	bool needsRepaint;

	Layout id(unsigned long long value) {
		this->_id = value;
		return *this;
	} // debug
	vector<RenderViewState> getFlattenedRenderViewStates() {
		vector<RenderViewState> result;
		result.push_back(this->renderViewState);

		Model model = this->model();
		for (Layout<boost::any> child : model.getItems()) {
			vector<RenderViewState> childFlattened = child.getFlattenedRenderViewStates();
			result.insert(result.end(), childFlattened.begin(), childFlattened.end());
		}
		return result;
	}
	Bounds calcBounds(CompleteStyle myStyle, Bounds parentBound) {
		// TODO :: set null to all properties as default & set default values while building
		// TODO :: maybe with caching? (for optimization)

		double winWidth = parentBound.w;
		double winHeight = parentBound.h;
		double width = myStyle.width > 0 ? myStyle.width : winWidth;
		double height = myStyle.height > 0 ? myStyle.height : winHeight;
		Bounds bounds;

		switch (myStyle.display) {
		case LayoutType::Flex:
			bounds = Bounds(0, 0, width, height);
			break;
		case LayoutType::Fixed:
			bounds = Bounds(
				myStyle.absolute._left > 0 ? myStyle.absolute._left : (
					myStyle.width > 0 ? winWidth - myStyle.width - myStyle.absolute._right : 0
					),
				myStyle.absolute._top > 0 ? myStyle.absolute._top : (
					myStyle.height > 0 ? winHeight - myStyle.height - myStyle.absolute._bottom : 0
					),
				myStyle.width > 0 ? myStyle.width : winWidth - myStyle.absolute._left - myStyle.absolute._right,
				myStyle.height > 0 ? myStyle.height : winHeight - myStyle.absolute._top - myStyle.absolute._bottom
			);
			break;
		}

		return bounds;
	}
	CompleteStyle calcStyle(CompleteStyle parentStyle) {
		// TODO:: overwrite specfic styles with parent style
		return this->style.overwriteWithDefault();
	}
	void repainted(sf::RenderTexture* texture) {
		this->renderViewState.updateTexture(texture);
		this->needsRepaint = false;
	}


protected:
	Style style;
	//std::vector<Layout> _children;

public:
	unsigned long long _id;

	// TODO :: dettach style properties from layout properties

	Layout<StateType>(bool initialNeedPaint = true) {
		this->renderViewState = RenderViewState();
		this->_id = -1; // TODO :: set incremental id (or random)
		this->_cachedModel = nullptr;
		this->needsRepaint = initialNeedPaint;
	}
	//template <typename... Layouts>
	//Layout(Layouts... layouts) : Layout() {
	//	this->_children = { layouts... };
	//}

	Model model() {
		if (this->_model == nullptr) {
			this->_model = &this->buildModel();
		}
		return *this->_model;
	}

	virtual Model buildModel() {
		return Model();
	};

	virtual bool shouldRepaint(StateType p) {
		//static_assert(is_base_of<Style, Props>::value, "Props must be a subclass of Style");
		//// as default, compare all properties of next style with previous style
		//CompleteStyle currentCompiledStyle = this->calcStyle(this->style);
		//CompleteStyle nextCompiledStyle = this->calcStyle(p);
		//if (currentCompiledStyle != nextCompiledStyle) return true;

		if (this->state != p) return true; // TODO :: check if != operator definition needed
		return false;
	}
	virtual void updateState(StateType newState);
	void updateCheck(StateType newState) {
		// check should repaint & mark as needs repaint
		if (this->shouldRepaint(newState)) this->needsRepaint = true;

		Model model = this->model();
		for (Layout<boost::any> child : model.getItems()) {
			child->updateCheck();
		}
	}
	RenderViewState lastPainting() {
		return this->renderViewState;
	} // get last painting of layout
	void render(sf::RenderWindow& window) {
		this->repaint(); // not force repaint
		vector<RenderViewState> flattenLayers = this->getFlattenedRenderViewStates();
		// TODO :: apply z-index
		for (RenderViewState layer : flattenLayers) {
			sf::Sprite sprite = layer.getSprite();
			window.draw(sprite);
		}
	} // render self & children layout to window
	void repaint(CompleteStyle parentStyle, Bounds parentBound) {
		if (!this->needsRepaint) return;

		// overwrite this style with default
		CompleteStyle style = this->calcStyle(parentStyle);

		// calculate bounds
		Bounds bounds = this->calcBounds(style, parentBound);

		// create render texture
		sf::RenderTexture* renderTexture = new sf::RenderTexture();
		renderTexture->create(parentBound.w, parentBound.h);

		// draw self
		this->build(*renderTexture, style, bounds);

		// draw children (calculate subordinates layout)
		vector<Layout> childrens;
		Model model = this->model();
		for (Layout<boost::any> child : model.getItems()) {
			childrens.push_back(child);
		}

		bool isRow = style.flexDirection == FlexDirection::Row;
		double totalFlex = 0;
		double totalWidth = 0;
		double totalHeight = 0;
		for (Layout child : childrens) {
			CompleteStyle childStyle = child.calcStyle(style);
			// TODO :: consider caching style (for optimization)
			if (childStyle.display == LayoutType::Fixed) continue;
			if (isRow) {
				if (childStyle.width > 0) totalWidth += childStyle.width;
				else totalFlex += childStyle.flex;
				totalHeight = std::max(totalHeight, childStyle.height);
			}
			else {
				if (childStyle.height > 0) totalHeight += childStyle.height;
				else totalFlex += childStyle.flex;
				totalWidth = std::max(totalWidth, childStyle.width);
			}
		}

		double remainingSpace = isRow ? bounds.w - totalWidth : bounds.h - totalHeight;
		double unitFlexSpace = totalFlex > 0 ? remainingSpace / totalFlex : 0;

		double curX = bounds.x;
		double curY = bounds.y;

		//cout << format("totalFlex: {}, remainingSpace: {}, unitFlexSpace: {}",
		//	totalFlex, remainingSpace, unitFlexSpace) << endl;

		for (Layout child : childrens) {
			CompleteStyle childStyle = child.calcStyle(style);
			switch (childStyle.display) {
			case LayoutType::Flex:
				if (isRow) {
					double width = childStyle.width;
					if (width == 0) width = unitFlexSpace * childStyle.flex;
					if (width < 0) width = 0;
					child.repaint(style, Bounds(curX, bounds.y, width, bounds.h));
					curX += width;
				}
				else {
					double height = childStyle.height;
					if (height == 0) height = unitFlexSpace * childStyle.flex;
					if (height < 0) height = 0;
					child.repaint(style, Bounds(bounds.x, curY, bounds.w, height));
					curY += height;
				}
				break;
			case LayoutType::Fixed:
				child.repaint(style, Bounds(0, 0, 0, 0));
				break;
			}
		}

		// save render texture to render view state
		this->repainted(renderTexture);
	} // repaint self & children layout and save to renderViewState

	void build(sf::RenderTexture& view, CompleteStyle style, Bounds bounds) {
		//cout << format("[Layout#{}] x: {}, y: {}, w: {}, h: {}, children: {}, text: \"{}...\"", 
		//	style.id, bounds.x, bounds.y, bounds.w, bounds.h, style.children.size(), style.text.substr(0, 8)) << endl;
		//if (style.display == LayoutType::Fixed) {
		//	cout << format("\tabsolute: top: {}, right: {}, bottom: {}, left: {}", 
		//		style.absolute._top, style.absolute._right, style.absolute._bottom, style.absolute._left) << endl;
		//}

		// ignore drawing self if width or height is under 0
		if (bounds.w > 0 && bounds.h > 0) {
			// consider border width
			double x = bounds.x + style.borderWidth;
			double y = bounds.y + style.borderWidth;
			double w = bounds.w - style.borderWidth * 2;
			double h = bounds.h - style.borderWidth * 2;

			sf::RectangleShape shape;
			shape.setPosition(x, y);
			shape.setSize(sf::Vector2f(float(w), float(h)));
			shape.setFillColor(style.backgroundColor);
			shape.setOutlineColor(style.borderColor);
			shape.setOutlineThickness(style.borderWidth);
			view.draw(shape);
		}

		// draw text if exists
		if (!style.text.empty()) {
			sf::Font font = Asset::Tracker::loadFont(style.font);
			sf::Text text;
			text.setString(style.text);
			text.setFont(font);
			text.setCharacterSize(style.fontSize);
			text.setFillColor(style.color);

			// apply justify content & align items as text alignment
			double tx = bounds.x + style.padding._left;
			double ty = bounds.y + style.padding._top;
			switch (style.justifyContent) { // horizontal
			case JustifyContent::Start:
				break;
			case JustifyContent::Center:
				tx += bounds.w / 2 - text.getLocalBounds().width / 2;
				break;
			case JustifyContent::End:
				tx += bounds.w - text.getLocalBounds().width;
				break;
			}
			switch (style.alignItems) { // vertical
			case AlignItems::Start:
				break;
			case AlignItems::Center:
				ty += bounds.h / 2 - text.getLocalBounds().height / 2;
				break;
			case AlignItems::End:
				ty += bounds.h - text.getLocalBounds().height;
				break;
			}
			text.setPosition(tx, ty);

			// TODO :: clip (overflow)
			//sf::View originalView = window.getView();
			//sf::View clipView(sf::FloatRect(x, y, w, h));
			//window.setView(clipView);
			view.draw(text);
			//window.setView(originalView);

			//cout << format("Text drawing: x: {}, y: {}, w: {}, h: {}", tx, ty, text.getLocalBounds().width, text.getLocalBounds().height) << endl;
		}
	}

	//template <typename... Layouts>
	//Layout children(Layouts... layouts) {
	//	this->_children = { layouts... };
	//	return *this;
	//}
	//Layout children(vector<Layout> layouts);
};

