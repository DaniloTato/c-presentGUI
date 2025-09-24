#pragma once

#include <string>
#include <string>

#include <cpresent/cpresent_wrapper.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

std::string blockToString(block_t value);
block_t stringToBlock(const std::string& hexStr);
std::string keyToHexString(const cp_key_t& key);
cp_key_t stringToKey(const std::string& s);
void updateKey(cp_key_t& currentKey, std::string newKey);


