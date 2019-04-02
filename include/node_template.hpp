#pragma once

#include <map>
#include <string>

#include "types.hpp"

class PinTemplate {
public:
	std::string name;
	PinType type;
	bool isImmediate;
};

class InputTemplate : public PinTemplate {
public:
};

class OutputTemplate : public PinTemplate {
public:
	std::string code;
	std::string returnValue;
};

class NodeTemplate {
public:
	std::vector<InputTemplate> inputs;
	std::vector<OutputTemplate> outputs;
};

using NodeLibrary = std::map<std::string, NodeTemplate>;

NodeLibrary& getTemplates();
void setTemplates(NodeLibrary& lib);