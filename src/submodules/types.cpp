#include "types.hpp"
#include <format>
#include <iostream>

using namespace std;

Cardinal::Cardinal() {
	this->_top = 0;
	this->_bottom = 0;
	this->_left = 0;
	this->_right = 0;
}

Cardinal::Cardinal(double value) {
	this->_top = value;
	this->_bottom = value;
	this->_left = value;
	this->_right = value;
}

Cardinal::Cardinal(double top, double bottom) {
	this->_top = top;
	this->_bottom = bottom;
	this->_left = 0;
	this->_right = 0;
}

Cardinal::Cardinal(double top, double right, double bottom, double left) {
	this->_top = top;
	this->_bottom = bottom;
	this->_left = left;
	this->_right = right;
}

Cardinal Cardinal::all(double value) {
	this->_top = value;
	this->_bottom = value;
	this->_left = value;
	this->_right = value;
	return *this;
}

Cardinal Cardinal::vertical(double value) {
	this->_top = value;
	this->_bottom = value;
	return *this;
}

Cardinal Cardinal::horizontal(double value) {
	this->_left = value;
	this->_right = value;
	return *this;
}

Cardinal Cardinal::top(double value) {
	this->_top = value;
	return *this;
}

Cardinal Cardinal::bottom(double value) {
	this->_bottom = value;
	return *this;
}

Cardinal Cardinal::left(double value) {
	this->_left = value;
	return *this;
}

Cardinal Cardinal::right(double value) {
	this->_right = value;
	return *this;
}