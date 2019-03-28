#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include "application_log.hpp"
#include "configuration_loader.hpp"

std::string fragShader {
	"#version 330\n"
	"uniform vec2 iResolution;"
	"void main() {"
	"	vec2 uv = gl_FragCoord.xy / iResolution.xy;"
	"	gl_FragColor = vec4(uv, 0.3, 1.);"
	"}"
};

int main() {
	bool running = true;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "RayMarching Editor");
	ImGui::SFML::Init(window);

	try {
		loadTemplates("kernels");
	}
	catch (std::exception& e) {
		logError(e.what());
	}

	sf::Clock delta;
	while (running) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			running = event.type != event.Closed;
		}

		window.clear();

		sf::Texture texture;
		texture.create(window.getSize().x, window.getSize().y);
		sf::Sprite sprite(texture);
		sf::Shader shader;
		shader.loadFromMemory(fragShader, sf::Shader::Fragment);
		shader.setUniform("iResolution", sf::Glsl::Vec2(window.getSize().x, window.getSize().y));

		window.draw(sprite, &shader);

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