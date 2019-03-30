#pragma once

#include <string>
#include <vector>

#include "id.hpp"
#include "node_template.hpp"
#include "pin.hpp"

class Pin;

class Node {
public:
	Node() : id(ID()) {}
	Node(std::string name) : id(ID()), name(name) {}

	NodeTemplate asTemplate();

	ID id;
	std::string name;
	std::vector<Pin> inputs;
	std::vector<Pin> outputs;
};