#pragma once

#include <any>
#include <array>
#include <string>
#include <vector>

#include "id.hpp"
#include "node_template.hpp"
#include "pin.hpp"

class Pin;
class InputPin;
class OutputPin;

void initializeAny(std::any& any, PinType type);

class Node {
public:
	Node() : id(ID()) {}
	Node(std::string name);

	NodeTemplate& asTemplate();

	ID id;
	std::string name;
	std::vector<InputPin> inputs;
	std::vector<OutputPin> outputs;
};