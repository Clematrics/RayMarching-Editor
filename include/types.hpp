#pragma once

#include "enum_to_string.hpp"

#define PinTypeDescription InvalidType = 0x00, Float, Vec3
DECLARE_ENUM(PinType, PinTypeDescription);