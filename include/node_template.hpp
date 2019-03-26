#pragma once

#include <map>
#include <string>

#include "types.hpp"

class InputTemplate {
public:
	std::string name;
	PinType type;
};

class OutputTemplate {
public:
	std::string name;
	PinType type;
	std::string code;
	std::string returnValue;
};

class NodeTemplate {
public:
	std::vector<InputTemplate> inputs;
	std::vector<OutputTemplate> outputs;
};

using NodeLibrary = std::map<std::string, NodeTemplate>;