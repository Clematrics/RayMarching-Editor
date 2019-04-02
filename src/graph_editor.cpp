#include "graph_editor.hpp"

#include <any>
#include <array>
#include <string>

#include "application_log.hpp"
#include "structs.hpp"

#include "node_template.hpp"
#include "ax/Widgets.h"

#include "util/zip.hpp"

namespace NodeEd = ax::NodeEditor;

Editor::Editor() : editorContext(NodeEd::CreateEditor()) {
}

Editor::~Editor() {
	NodeEd::DestroyEditor(editorContext.operator->());
}

Editor::Editor(const Editor& editor) : editorContext(editor.editorContext), graph(editor.graph) {
}

void Editor::display() {
	NodeEd::SetCurrentEditor(editorContext.operator->());
	NodeEd::Begin("Nodes editor");

	auto startPositionCursor = ImGui::GetCursorScreenPos();
	displayNodes();
	ImGui::SetCursorScreenPos(startPositionCursor);

	displayLinks();
	displayPopup();
	displayContextMenu();

	NodeEd::End();
}

Graph& Editor::getGraph() {
	return graph;
}

void Editor::addNode(std::string name) {
	graph.nodes.emplace_back(name);
}

void Editor::displayNodes() {
	NodeEd::PushStyleVar(NodeEd::StyleVar_NodePadding, ImVec4(8, 4, 8, 8));

	for (auto& node : graph.nodes) {
		NodeEd::BeginNode((uint64_t)node.id);
		ImGui::PushID((uint64_t)node.id);

		ImGui::BeginVertical("node");
		displayHeader(node);

		ImGui::BeginHorizontal("content");
        ImGui::Spring(0, 0);

		displayInputs(node);
		displayOutputs(node);

		ImGui::EndHorizontal();
		ImGui::EndVertical();

		NodeEd::EndNode();

		auto drawList = NodeEd::GetNodeBackgroundDrawList((uint64_t)node.id);
		// padding constants for the header (see builders.cpp, line 62)
		const auto halfBorderWidth = NodeEd::GetStyle().NodeBorderWidth * 0.5f;
		auto a = ImVec2(currentHeaderTopLeft.x - (8 - halfBorderWidth), currentHeaderTopLeft.y - (4 - halfBorderWidth));
		auto b = ImVec2(currentHeaderBottomRight.x + (8 - halfBorderWidth), currentHeaderBottomRight.y);
		drawList->AddRectFilled(a, b, IM_COL32(0, 0, 200, 255), 12., ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight);

		ImGui::PopID();
	}

	NodeEd::PopStyleVar();
}

void Editor::displayHeader(Node& node) {
	ImGui::BeginHorizontal("header");

	ImGui::Spring();
	ImGui::TextUnformatted(node.name.c_str());
	ImGui::Spring(1);
	ImGui::Dummy(ImVec2(0, 28));
	ImGui::Spring(0);

	ImGui::EndHorizontal();
	currentHeaderTopLeft = ImGui::GetItemRectMin();
	currentHeaderBottomRight = ImGui::GetItemRectMax();

	ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.y * 2.0f);
}

void Editor::displayInputs(Node& node) {
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotAlignment, ImVec2(0, 0.5f));
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotSize, ImVec2(0, 0));

	ImGui::BeginVertical("inputs", ImVec2(0, 0), 0.0f);
	for (auto& [ input, pin ] : zip(node.asTemplate().inputs, node.inputs)) {
		displayPin(input, pin);
		ImGui::Spring(1, 0);
	}
	ImGui::EndVertical();

	NodeEd::PopStyleVar(2);
}

void Editor::displayOutputs(Node& node) {
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotAlignment, ImVec2(1.0f, 0.5f));
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotSize, ImVec2(0, 0));

	ImGui::Spring(1);
	ImGui::BeginVertical("outputs", ImVec2(0, 0), 1.0f);
	for (auto& [ output, pin ] : zip(node.asTemplate().outputs, node.outputs)) {
		displayPin(output, pin);
		ImGui::Spring(1, 0);
	}
	ImGui::EndVertical();

	NodeEd::PopStyleVar(2);
}


void Editor::displayPin(InputTemplate& input, Pin& pin) {
	NodeEd::BeginPin((uint64_t)pin.id, NodeEd::PinKind::Input);

	ImGui::BeginHorizontal((uint64_t)pin.id);
	ImGui::Spring(0, 0);

	displayPinSocket(input.type, pin.isConnected());
	ImGui::Spring(0);
	displayPinContent(input, pin);

	ImGui::BeginVertical("pin name");
	ImGui::Spring(1);
	ImGui::TextUnformatted(input.name.c_str());
	ImGui::Spring(1);
	ImGui::EndVertical();

	ImGui::Spring(0);
	ImGui::EndHorizontal();

	NodeEd::EndPin();
}

void Editor::displayPin(OutputTemplate& output, Pin& pin) {
	NodeEd::BeginPin((uint64_t)pin.id, NodeEd::PinKind::Output);

	ImGui::BeginHorizontal((uint64_t)pin.id);
	ImGui::Spring(0);

	ImGui::BeginVertical("pin name");
	ImGui::Spring(1);
	ImGui::TextUnformatted(output.name.c_str());
	ImGui::Spring(1);
	ImGui::EndVertical();

	displayPinContent(output, pin);
	ImGui::Spring(0);
	displayPinSocket(output.type, pin.isConnected());

	ImGui::Spring(0);
	ImGui::EndHorizontal();

	NodeEd::EndPin();
}

void Editor::displayPinContent(PinTemplate& pinTemplate, Pin& pin) {
	if (!pinTemplate.isImmediate)
		return;

	ImGui::BeginVertical("pin immediate");
	ImGui::Spring(0);

	ImGui::PushItemWidth(100.f);
	switch(pinTemplate.type) {
		case PinType::Float: {
			Float& a = std::any_cast<Float&>(pin.immediate);
			ImGui::InputScalar("##float", ImGuiDataType_Float, &(a.v), nullptr, nullptr, "%.3f");
			break;
		}
		case PinType::Vec3: {
			Vec3& arr = std::any_cast<Vec3&>(pin.immediate);
			ImGui::InputScalar("##vec3_0", ImGuiDataType_Float, &(arr.x), nullptr, nullptr, "%.3f");
			ImGui::Spring(1, 0);
			ImGui::InputScalar("##vec3_1", ImGuiDataType_Float, &(arr.y), nullptr, nullptr, "%.3f");
			ImGui::Spring(1, 0);
			ImGui::InputScalar("##vec3_2", ImGuiDataType_Float, &(arr.z), nullptr, nullptr, "%.3f");
			break;
		}
		default:
			;
	}
	ImGui::PopItemWidth();

	ImGui::Spring(0);
	ImGui::EndVertical();
}

void Editor::displayPinSocket(PinType type, bool connected) {
	ax::Widgets::IconType icon;
	ImColor color;
	switch(type) {
		case PinType::Float: 	icon = ax::Widgets::IconType::Circle; 	color = IM_COL32(200, 220, 020, 255); break;
		case PinType::Vec3: 	icon = ax::Widgets::IconType::Circle; 	color = IM_COL32(220, 020, 020, 255); break;
		default:				icon = ax::Widgets::IconType::Diamond;	color = IM_COL32(020, 020, 220, 255);
	}
	ax::Widgets::Icon(ImVec2(24, 24), icon, connected, color, ImColor(32, 32, 32, 128));
}

void Editor::displayLinks() {
}

void Editor::displayPopup() {
}

void Editor::displayContextMenu() {
}

