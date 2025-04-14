#include "../include/Block.h"
#include <sstream>
#include <functional>
#include <iostream>

Block::Block(int idx, const std::string& data, const std::string& prevHash)
    : index(idx), data(data), prevHash(prevHash) {
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    
    std::stringstream ss;
    ss << index << data << prevHash;
    std::string input = ss.str();
    std::string hashed = std::to_string(std::hash<std::string>{}(input));

    return hashed;
}


Block::Block(int idx, const std::string& data, const std::string& prevHash, const std::string& hash)
    : index(idx), data(data), prevHash(prevHash), hash(hash) {}

