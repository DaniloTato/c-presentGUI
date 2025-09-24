#include <include/utils.hpp>
#include <sstream>

std::string blockToString(block_t value) {
    std::string result;
    for (int i = 7; i >= 0; --i) {
        char c = (value >> (i * 8)) & 0xFF;
        if (c != 0) result += c;
    }
    return result;
}

block_t stringToBlock(const std::string& s) {
    block_t value = 0;
    for (size_t i = 0; i < s.size() && i < 8; ++i) {
        value <<= 8;
        value |= static_cast<uint8_t>(s[i]);
    }
    return value;
}

std::string keyToHexString(const cp_key_t& key) {
    std::ostringstream oss;
    oss << std::hex << key.hi << " " << key.lo;
    return oss.str();
}

cp_key_t stringToKey(const std::string& s) {
    cp_key_t k = {0, 0};
    std::string padded = s;
    if (padded.size() < 16) {
        padded += std::string(16 - padded.size(), '0'); // rellenar a 16 chars
    } else if (padded.size() > 16) {
        padded = padded.substr(0, 16);
    }

    k.hi = 0;
    k.lo = 0;

    for (size_t i = 0; i < 8; ++i) k.hi = (k.hi << 8) | static_cast<uint8_t>(padded[i]);
    for (size_t i = 8; i < 16; ++i) k.lo = (k.lo << 8) | static_cast<uint8_t>(padded[i]);

    return k;
}

void updateKey(cp_key_t& currentKey, std::string newKey){
    currentKey = stringToKey(newKey);
    set_key(currentKey);
}