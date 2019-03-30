#include "templates_loader.hpp"

#include <filesystem>
#include <fstream>

#include "application_log.hpp"
#include "types.hpp"

std::vector<InputTemplate> loadInputTemplate(const picojson::value jsonInputs) {
	std::vector<InputTemplate> inputs;
	for (const auto& object : jsonInputs.get<picojson::array>()) {
		InputTemplate input;
		input.name = 					object.get("name").get<std::string>();
		input.type = stringToPinType(	object.get("type").get<std::string>() );
		inputs.emplace_back(input);
	}
	return inputs;
}

std::vector<OutputTemplate> loadOutputTemplate(const picojson::value jsonOutputs) {
	std::vector<OutputTemplate> outputs;
	for (const auto& object : jsonOutputs.get<picojson::array>()) {
		OutputTemplate output;
		output.name = 					object.get("name").get<std::string>();
		output.type = stringToPinType(	object.get("type").get<std::string>() );
		output.code = 					object.get("code").get<std::string>();
		output.returnValue = 			object.get("value").get<std::string>();
		outputs.emplace_back(output);
	}
	return outputs;
}

NodeLibrary loadTemplateFile(const std::string filePath) {
	std::ifstream stream(filePath);
	if (!stream.is_open()) {
		logError("Cannot open the file " + filePath + " to load node templates");
		return NodeLibrary();
	}

	picojson::value value;
	picojson::parse(value, stream);

	NodeLibrary library;

	for (const auto& object : value.get<picojson::array>()) {
		NodeTemplate nodeTemplate;
		nodeTemplate.inputs = loadInputTemplate(object.get("inputs"));
		nodeTemplate.outputs = loadOutputTemplate(object.get("outputs"));

		library.emplace(object.get("name").get<std::string>(), nodeTemplate);
	}

	return library;
}

NodeLibrary loadTemplates(const std::string path) {
	NodeLibrary loadedNodes;
	logDebug("Loading node templates...");

	try {
		for (const auto& file : std::filesystem::directory_iterator(path))
			if (file.is_regular_file() && file.path().extension() == ".json") {
				logDebug("	- from file " + file.path().string());
				auto justLoaded = loadTemplateFile(file.path().string());
				loadedNodes.merge(justLoaded);
			}
	} catch (std::exception& e) {
		logError(e.what());
	}

	logDebug(std::to_string(loadedNodes.size()) + " node templates were loaded");
	return loadedNodes;
}