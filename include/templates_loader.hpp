#pragma once

#include <string>

#include "picojson.h"

#include "node_template.hpp"

// InputTemplate loadInputTemplate(const picojson::value& jsonInputs);
// OutputTemplate loadOutputTemplate(const picojson::value& jsonOutputs);
// NodeLibrary loadTemplateFile(const std::string& filePath);
NodeLibrary loadTemplates(const std::string& path);