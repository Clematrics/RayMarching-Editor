#pragma once

#include <memory>

#include "link.hpp"
#include "node.hpp"

class Node;
class Link;

class Pin {
public:
	std::shared_ptr<Node> parentNode;
	std::shared_ptr<Link> link;
};