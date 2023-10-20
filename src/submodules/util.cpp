#include "util.hpp"
#include <chrono>
#include <ctime>

using namespace std;

double getCurrentTime() {
	return chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000000000.0;
}