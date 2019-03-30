#pragma once

#include <string>
#include <vector>

#include "pin.hpp"

class Pin;

class Node {
public:
	unsigned int id;
	std::string name;
	std::vector<Pin> inputs;
	std::vector<Pin> outputs;
};