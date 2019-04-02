#pragma once

#include <cstdint>

static uint64_t global_id_counter = 0;

class ID {
public:
	ID() : id(global_id_counter++) {}
	operator uint64_t() const { return id; }
private:
	const uint64_t id;
};