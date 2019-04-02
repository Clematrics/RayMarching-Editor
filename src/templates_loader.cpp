#include "templates_loader.hpp"

#include <filesystem>
#include <fstream>
#include <vector>

#include "application_log.hpp"
#include "node_template.hpp"
#include "types.hpp"

template <class PinTemplate>
PinTemplate loadPinTemplate(const picojson::value& object) {
	PinTemplate pin;
	pin.name = 					object.get("name").get<std::string>();
	pin.type = stringToPinType(	object.get("type").get<std::string>() );

	auto immediateObject = object.get("immediate");
	pin.isImmediate = 			immediateObject.is<picojson::null>() ? false : true;
	return pin;
}

InputTemplate loadInputTemplate(const picojson::value& object) {
	InputTemplate input = loadPinTemplate<InputTemplate>(object);
	return input;
}

OutputTemplate loadOutputTemplate(const picojson::value& object) {
	OutputTemplate output = loadPinTemplate<OutputTemplate>(object);
	output.code = 				object.get("code").get<std::string>();
	output.returnValue = 		object.get("value").get<std::string>();
	return output;
}

NodeLibrary loadTemplateFile(const std::string& filePath) {
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
		for (auto& input : object.get("inputs").get<picojson::array>())
			nodeTemplate.inputs.emplace_back(loadInputTemplate(input));
		for (auto& output : object.get("outputs").get<picojson::array>())
			nodeTemplate.outputs.emplace_back(loadOutputTemplate(output));

		library.emplace(object.get("name").get<std::string>(), nodeTemplate);
	}

	return library;
}

NodeLibrary loadTemplates(const std::string& path) {
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
	setTemplates(loadedNodes);
	return loadedNodes;
}