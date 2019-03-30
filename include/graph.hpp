#pragma once

#include <vector>

#include "link.hpp"
#include "node.hpp"

class Graph {
public:
	std::vector<Node> nodes;
	std::vector<Link> links;
};