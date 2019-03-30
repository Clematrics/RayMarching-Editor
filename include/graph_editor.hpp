#pragma once

#include <vector>

#include "node.hpp"
#include "link.hpp"

#include "NodeEditor.h"

static ax::NodeEditor::EditorContext* editor;

static std::vector<Node> nodes;
static std::vector<Link> links;

void addNode(Node node);

void initializeEditor();
void showEditor();
void destroyEditor();