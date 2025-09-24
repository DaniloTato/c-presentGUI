#include <include/utils.hpp>

#include <sstream>

std::string blockToHexString(block_t value) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << value; // convert to hex string
    return oss.str(); // returns string like "123" for 0x123
}

block_t stringToBlock(const std::string& hexStr) {
    block_t value;
    std::stringstream ss;
    ss << std::hex << hexStr;
    ss >> value;
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
        padded = std::string(16 - padded.size(), '0') + padded;
    } else if (padded.size() > 16) {
        padded = padded.substr(0, 16);
    }

    k.hi = std::stoull(padded.substr(0, 8), nullptr, 16);
    k.lo = std::stoull(padded.substr(8, 8), nullptr, 16);

    return k;
}

void updateKey(cp_key_t& currentKey, std::string newKey){
    currentKey = stringToKey(newKey);
    set_key(currentKey);
}