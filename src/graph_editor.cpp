#include "graph_editor.hpp"

#include <string>

#include "node_template.hpp"
#include "ax/Widgets.h"

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

void Editor::displayNodes() {
	NodeEd::PushStyleVar(NodeEd::StyleVar_NodePadding, ImVec4(8, 4, 8, 8));

	for (auto& node : graph.nodes) {
		NodeEd::BeginNode((uint64_t)node.id);
		ImGui::PushID(node.id);

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
		// constantes de padding du header (voir builders.cpp, l.62)
		const auto halfBorderWidth = NodeEd::GetStyle().NodeBorderWidth * 0.5f;
		auto a = ImVec2(currentHeaderTopLeft.x - (8 - halfBorderWidth), currentHeaderTopLeft.y - (4 - halfBorderWidth));
		auto b = ImVec2(currentHeaderBottomRight.x + (8 - halfBorderWidth), currentHeaderBottomRight.y);
		drawList->AddRectFilled(a, b, IM_COL32(0, 0, 200, 255), 12., ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight);

		ImGui::PopID();
	}

	NodeEd::PopStyleVar();
}

void Editor::displayHeader(Node node) {
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

void Editor::displayInputs(Node node) {
	static int id = 0;
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotAlignment, ImVec2(0, 0.5f));
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotSize, ImVec2(0, 0));

	ImGui::BeginVertical("inputs", ImVec2(0, 0), 0.0f);
	for (auto& input : node.asTemplate().inputs) {

		NodeEd::BeginPin(id++, NodeEd::PinKind::Input);
		ImGui::BeginHorizontal(id++);
		displayPin(input.type, false);
		ImGui::Spring(0);
		ImGui::TextUnformatted(input.name.c_str());
		ImGui::Spring(0);
		ImGui::EndHorizontal();
		NodeEd::EndPin();

		ImGui::Spring(1, 0);
	}
	ImGui::EndVertical();

	NodeEd::PopStyleVar(2);
}

void Editor::displayOutputs(Node node) {
	static int id = 0;
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotAlignment, ImVec2(1.0f, 0.5f));
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotSize, ImVec2(0, 0));

	ImGui::Spring(1);
	ImGui::BeginVertical("outputs", ImVec2(0, 0), 1.0f);
	for (auto& output : node.asTemplate().outputs) {

		NodeEd::BeginPin(id++, NodeEd::PinKind::Output);
		ImGui::BeginHorizontal(id++);

		// ImGui::Spring(0);
		ImGui::TextUnformatted(output.name.c_str());
		ImGui::Spring(0);
		displayPin(output.type, false);

		ImGui::EndHorizontal();
		NodeEd::EndPin();


		ImGui::Spring(1, 0);
	}
	// ImGui::Spring(1, 0);
	ImGui::EndVertical();

	NodeEd::PopStyleVar(2);
}

void Editor::displayPin(PinType type, bool connected) {
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

