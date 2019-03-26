#pragma once

#include <string>
#include <vector>

#include "picojson.h"

#include "node_template.hpp"

std::vector<InputTemplate> loadInputTemplate(const picojson::value jsonInputs);
std::vector<OutputTemplate> loadOutputTemplate(const picojson::value jsonOutputs);
NodeLibrary loadTemplateFile(const std::string filePath);
NodeLibrary loadTemplates(const std::string path);