#include "enum_to_string.hpp"

std::vector<std::string> splitString(std::string str, char sep) {
	std::vector<std::string> vecString;
	std::string item;

	std::stringstream stringStream(str);

	while (std::getline(stringStream, item, sep))
	{
		vecString.push_back(item);
	}

	return vecString;
}