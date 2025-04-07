#include "../include/Blockchain.h"

Blockchain::Blockchain() {
    chain.emplace_back(0, "Genesis Block", "0");
}

void Blockchain::addBlock(const std::string& data) {
    const Block& prev = chain.back();
    chain.emplace_back(prev.index + 1, data, prev.hash);
}

const std::vector<Block>& Blockchain::getChain() const {
    return chain;
}

bool Blockchain::isValid() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        if (chain[i].prevHash != chain[i - 1].hash)
            return false;
        if (chain[i].hash != chain[i].calculateHash())
            return false;
    }
    return true;
}
