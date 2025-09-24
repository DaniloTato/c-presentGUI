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