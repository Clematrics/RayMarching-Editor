#pragma once

#include <any>
#include <algorithm>
#include <memory>
#include <variant>
#include <vector>

#include "id.hpp"
#include "link.hpp"
#include "node.hpp"
#include "structs.hpp"

class Node;
class Link;

class Pin {
public:
	Pin() : id(ID()) {}
	virtual bool isConnected() const { return false; }
	ID id;
	std::shared_ptr<Node> parentNode;
	std::any immediate;
};

class InputPin : public Pin {
public:
	InputPin() { Pin(); }
	bool isConnected() const { return (bool)link; }
	std::shared_ptr<Link> link;
};

class OutputPin : public Pin {
public:
	OutputPin() { Pin(); }
	bool isConnected() const {return std::any_of(links.begin(), links.end(), [](const auto& link){ return (bool)link; }); }
	std::vector<std::shared_ptr<Link>> links;
};