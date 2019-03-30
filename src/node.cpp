#include "node.hpp"

#include "node_template.hpp"

NodeTemplate Node::asTemplate() {
	return getTemplates()[name];
}