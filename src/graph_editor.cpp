#include "graph_editor.hpp"

#include <string>

#include "node_template.hpp"
#include "ax/Widgets.h"

namespace NodeEd = ax::NodeEditor;

void addNode(Node node) {
	nodes.push_back(node);
}

void initializeEditor() {
	editor = NodeEd::CreateEditor();
}

static ImVec2 headerRectMin;
static ImVec2 headerRectMax;

void drawHeader(std::string name) {
	ImGui::BeginHorizontal("header");

	ImGui::Spring();
	ImGui::TextUnformatted(name.c_str());
	ImGui::Spring(1);
	ImGui::Dummy(ImVec2(0, 28));
	ImGui::Spring(0);

	ImGui::EndHorizontal();
	headerRectMin = ImGui::GetItemRectMin();
	headerRectMax = ImGui::GetItemRectMax();

	ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.y * 2.0f);
}

void drawPin(PinType type, bool connected) {
	ax::Widgets::IconType icon;
	ImColor color;
	switch(type) {
		case PinType::Float: 	icon = ax::Widgets::IconType::Circle; 	color = IM_COL32(200, 220, 020, 255); break;
		case PinType::Vec3: 	icon = ax::Widgets::IconType::Circle; 	color = IM_COL32(220, 020, 020, 255); break;
		default:				icon = ax::Widgets::IconType::Diamond;	color = IM_COL32(020, 020, 220, 255);
	}
	ax::Widgets::Icon(ImVec2(24, 24), icon, connected, color, ImColor(32, 32, 32, 128));
}

void drawInputs(std::vector<InputTemplate> inputs) {
	static int id = 0;
	id = 0;
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotAlignment, ImVec2(0, 0.5f));
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotSize, ImVec2(0, 0));

	ImGui::BeginVertical("inputs", ImVec2(0, 0), 0.0f);
	for (auto& input : inputs) {

		NodeEd::BeginPin(id, NodeEd::PinKind::Input);
		ImGui::BeginHorizontal(id);
		drawPin(input.type, false);
		ImGui::Spring(0);
		ImGui::TextUnformatted(input.name.c_str());
		ImGui::Spring(0);
		ImGui::EndHorizontal();
		NodeEd::EndPin();

		ImGui::Spring(1, 0);
		id++;
	}
	ImGui::EndVertical();

	NodeEd::PopStyleVar(2);
}

void drawOutputs(std::vector<OutputTemplate> outputs) {
	static int id = 0;
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotAlignment, ImVec2(1.0f, 0.5f));
	NodeEd::PushStyleVar(NodeEd::StyleVar_PivotSize, ImVec2(0, 0));

	ImGui::Spring(1);
	ImGui::BeginVertical("outputs", ImVec2(0, 0), 1.0f);
	for (auto& output : outputs) {

		NodeEd::BeginPin(id, NodeEd::PinKind::Output);
		ImGui::BeginHorizontal(id);

		// ImGui::Spring(0);
		ImGui::TextUnformatted(output.name.c_str());
		ImGui::Spring(0);
		drawPin(output.type, false);

		ImGui::EndHorizontal();
		NodeEd::EndPin();


		ImGui::Spring(1, 0);
		id++;
	}
	// ImGui::Spring(1, 0);
	ImGui::EndVertical();

	NodeEd::PopStyleVar(2);
}

void finishNode(unsigned int id) {
	auto drawList = NodeEd::GetNodeBackgroundDrawList(id);
	// constantes de padding du header (voir builders.cpp, l.62)
	const auto halfBorderWidth = NodeEd::GetStyle().NodeBorderWidth * 0.5f;
	auto a = ImVec2(headerRectMin.x - (8 - halfBorderWidth), headerRectMin.y - (4 - halfBorderWidth));
	auto b = ImVec2(headerRectMax.x + (8 - halfBorderWidth), headerRectMax.y);
	drawList->AddRectFilled(a, b, IM_COL32(0, 0, 200, 255), 12., ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight);
}

void drawNodes() {
	NodeEd::PushStyleVar(NodeEd::StyleVar_NodePadding, ImVec4(8, 4, 8, 8));

	for (auto& node : nodes) {
		NodeEd::BeginNode(node.id);
		ImGui::PushID(node.id);

		ImGui::BeginVertical("node");
		drawHeader(node.name);

		ImGui::BeginHorizontal("content");
        ImGui::Spring(0, 0);

		drawInputs(getTemplates()[node.name].inputs);
		drawOutputs(getTemplates()[node.name].outputs);

		ImGui::EndHorizontal();
		ImGui::EndVertical();

		NodeEd::EndNode();
		finishNode(node.id);
		ImGui::PopID();
	}

	NodeEd::PopStyleVar();
}

void showEditor() {
	NodeEd::SetCurrentEditor(editor);
	NodeEd::Begin("Nodes editor");

	auto startPositionCursor = ImGui::GetCursorScreenPos();
	drawNodes();


	ImGui::SetCursorScreenPos(startPositionCursor);

	NodeEd::End();
}

void destroyEditor () {
	NodeEd::DestroyEditor(editor);
}