#pragma once
#include <iostream>
#include <format>

using namespace std;

class StarcraftException : public exception {
public:
	StarcraftException(string message);
};