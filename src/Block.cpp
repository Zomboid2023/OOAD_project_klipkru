#include "../include/Block.h"
#include <sstream>
#include <functional>

Block::Block(int idx, const std::string& data, const std::string& prevHash)
    : index(idx), data(data), prevHash(prevHash) {
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << data << prevHash;
    return std::to_string(std::hash<std::string>{}(ss.str()));
}
