#include <include/utils.hpp>

#include <sstream>

std::string toHex(block_t value) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << value;
    return oss.str();
}

block_t fromHex(const std::string &hexStr) {
    block_t value = 0;
    std::stringstream ss;
    ss << std::hex << hexStr;
    ss >> value;
    return value;
}

std::vector<block_t> stringToBlocks(const std::string &str) {
    std::vector<block_t> blocks;
    for (size_t i = 0; i < str.size(); i += 8) {
        block_t block = 0;
        for (size_t j = 0; j < 8; j++) {
            block <<= 8;
            if (i + j < str.size())
                block |= static_cast<unsigned char>(str[i + j]);
        }
        blocks.push_back(block);
    }
    return blocks;
}

std::string blocksToString(const std::vector<block_t> &blocks) {
    std::string result;
    for (block_t block : blocks) {
        for (int i = 7; i >= 0; i--) {
            char c = static_cast<char>((block >> (8 * i)) & 0xFF);
            if (c != '\0') result.push_back(c);
        }
    }
    return result;
}

std::vector<block_t> encryptString(const std::string &str) {
    auto blocks = stringToBlocks(str);
    for (auto &b : blocks)
        b = encrypt_block(b);
    return blocks;
}

std::string decryptString(const std::vector<block_t> &encBlocks) {
    std::vector<block_t> decBlocks;
    for (auto b : encBlocks)
        decBlocks.push_back(decrypt_block(b));
    return blocksToString(decBlocks);
}