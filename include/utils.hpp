#pragma once

#include <string>
#include <string>

#include <cpresent/cpresent_wrapper.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

std::string blockToHexString(block_t value);
block_t stringToBlock(const std::string& hexStr);

