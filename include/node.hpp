#pragma once

#include <string>
#include <vector>

#include "pin.hpp"

class Node {
public:
	std::string name;
	std::vector<Pin> inputs;
	std::vector<Pin> outputs;
}