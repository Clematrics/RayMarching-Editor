#pragma once

#include <memory>
#include <vector>

#include "graph.hpp"
#include "node.hpp"
#include "link.hpp"

#include "NodeEditor.h"

class Editor {
public:
	Editor();
	~Editor();

	Editor(const Editor&);

	void display();
	Graph& getGraph();
private:
	void displayNodes();
	void displayHeader(Node node);
	void displayInputs(Node node);
	void displayOutputs(Node node);
	void displayPin(PinType type, bool connected);
	void displayLinks();
	void displayPopup();
	void displayContextMenu();

	Graph graph;
	std::shared_ptr<ax::NodeEditor::EditorContext> editorContext;

	ImVec2 currentHeaderTopLeft, currentHeaderBottomRight;
};