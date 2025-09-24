#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <string>


#include <cpresent/cpresent_wrapper.h>

std::string toHex(block_t value);

block_t fromHex(const std::string &hexStr);

std::vector<block_t> stringToBlocks(const std::string &str);

std::string blocksToString(const std::vector<block_t> &blocks);

std::vector<block_t> encryptString(const std::string &str);

std::string decryptString(const std::vector<block_t> &encBlocks);

block_t encrypt_block(block_t block);
block_t decrypt_block(block_t block);

#endif