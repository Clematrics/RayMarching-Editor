#pragma once

#include <vector>

#include "imgui.h"

namespace ImGui {
	// class Graph {
	// 	std::vector<Node> nodes;
	// 	ImVec2 center;
	// };

	// class Node {
	// 	ImVec2 position;
	// 	bool selected;
	// 	bool collapsed;
	// };

	// enum class PinFlow {
	// 	Input, Output
	// };

	// enum class PinType {
	// 	Integer,
	// 	Float,
	// 	Array,
	// };

	// class Pin {
	// 	PinFlow flow;
	// 	PinType type;
	// 	std::vector<Pin*> connectedTo; // connectedTo only contains pins if it's an output pin
	// };

	// class Link {
	// 	bool selected;
	// };

	// bool BeginGraph();					// return true if graph is displayed
	// void EndGraph();					// only call if beginNode return true

	// bool BeginNode(ImVec2 pos = ImVec2(0., 0.));	// return true if node is displayed
	// void EndNode();									// only call if beginNode return true

	// bool BeginPin(PinFlow flow);	// return true if pin is displayed
	// void EndPin();					// only call if beginNode return true
}