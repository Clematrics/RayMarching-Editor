#pragma once

#include <memory>

#include "pin.hpp"

class Pin;

class Link {
public:
	std::shared_ptr<Pin> startPin, endPin;
};