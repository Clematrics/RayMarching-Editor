#pragma once

#include <iostream>
#include <sstream>
#include <string>

#define ENABLE_LOG

static std::stringstream debugStream;

inline void logDebug(const std::string& msg);
inline void logError(const std::string& msg);
inline void logFatal(const std::string& msg);

void showDebugConsole();