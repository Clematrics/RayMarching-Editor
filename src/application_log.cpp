#include "application_log.hpp"

#include "imgui.h"

inline void logDebug(const std::string& msg) {
	#ifdef ENABLE_LOG
	debugStream << msg << "\n";
	#endif
}

inline void logError(const std::string& msg) {
	#ifdef ENABLE_LOG
	debugStream << "ERROR : " << msg << "\n";
	#endif
}

inline void logFatal(const std::string& msg) {
	#ifdef ENABLE_LOG
	debugStream << "FATAL : " << msg << "\n";
	#endif
}

void showDebugConsole() {
	ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
	if(!ImGui::Begin("Application log")) {
		ImGui::End();
		return;
	}

	debugStream.flush();
	std::string log = debugStream.str();
	ImGui::TextUnformatted(&*(log.begin()), &*(log.end()));
	ImGui::End();
}