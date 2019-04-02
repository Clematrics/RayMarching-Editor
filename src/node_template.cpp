#include "node_template.hpp"

static NodeLibrary templates;

NodeLibrary& getTemplates() {
	return templates;
}

void setTemplates(NodeLibrary& lib) {
	templates = lib;
}