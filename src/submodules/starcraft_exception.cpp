#include "starcraft_exception.hpp"

StarcraftException::StarcraftException(string message) : exception(message.c_str()) {}