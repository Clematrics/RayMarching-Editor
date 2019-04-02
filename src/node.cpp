#include "node.hpp"

#include "node_template.hpp"
#include "structs.hpp"

void initializeAny(std::any& any, PinType type) {
	switch (type) {
	case PinType::Float:	any = Float();	break;
	case PinType::Vec3:		any = Vec3();	break;
	default:				any = false;
	}
}

NodeTemplate& Node::asTemplate() {
	return getTemplates()[name];
}

Node::Node(std::string name) : id(ID()), name(name) {
	const NodeTemplate& template_ = getTemplates()[name];
	inputs.reserve(template_.inputs.size());
	outputs.reserve(template_.outputs.size());
	for (auto& pinTemplate : template_.inputs) {
		InputPin pin;
		if (pinTemplate.isImmediate)
			initializeAny(pin.immediate, pinTemplate.type);
		inputs.emplace_back(pin);
	}
	for (auto& pinTemplate : template_.outputs) {
		OutputPin pin;
		if (pinTemplate.isImmediate)
			initializeAny(pin.immediate, pinTemplate.type);
		outputs.emplace_back(pin);
	}
}