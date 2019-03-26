#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include "application_log.hpp"
#include "configuration_loader.hpp"

int main() {
	bool running = true;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "RayMarching Editor");
	ImGui::SFML::Init(window);

	try {
		loadTemplates("kernels");
	}
	catch (std::exception& e) {
		debug(e.what());
	}

	sf::Clock delta;
	while (running) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			running = event.type != event.Closed;
		}

		window.clear();
		ImGui::SFML::Update(window, delta.restart());
		ImGui::ShowDemoWindow();
		showDebugConsole();

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	window.close();

	return 0;
}