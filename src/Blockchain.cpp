#include "../include/Blockchain.h"
#include "../include/Block.h"
#include <sstream>
#include <iostream>

Blockchain::Blockchain() {
    chain.emplace_back(0, "Genesis Block", "0");
}

void Blockchain::addBlock(const std::string& data) {

    const Block& prevBlock = chain.back();
    Block newBlock(prevBlock.index + 1, data, prevBlock.hash);
    chain.emplace_back(newBlock);
    
}

const std::vector<Block>& Blockchain::getChain() const {
    return chain;
}

bool Blockchain::isValid() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        if (chain[i].prevHash != chain[i - 1].hash) return false;
    }
    return true;
}

std::string Blockchain::serialize() const {
    std::ostringstream oss;
    for (const auto& block : chain) {
        oss << block.index << "|" << block.data << "|" << block.hash << "|" << block.prevHash << "\n";
    }
    return oss.str();
}

void Blockchain::deserialize(const std::string& data) {
    chain.clear();
    std::stringstream ss(data);
    std::string line;
    while (std::getline(ss, line)) {
        std::stringstream ls(line);
        std::string indexStr, dataStr, hashStr, prevHashStr;
        std::getline(ls, indexStr, '|');
        std::getline(ls, dataStr, '|');
        std::getline(ls, hashStr, '|');
        std::getline(ls, prevHashStr, '|');
        Block b(std::stoi(indexStr), dataStr, prevHashStr, hashStr); // use the new constructor
        chain.push_back(b);

    }
    if (chain.empty()) {
        chain.emplace_back(0, "Genesis Block", "0");
    }
}
