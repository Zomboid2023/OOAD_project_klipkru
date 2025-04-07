#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include "Block.h"

class Blockchain {
private:
    std::vector<Block> chain;

public:
    Blockchain();
    void addBlock(const std::string& data);
    const std::vector<Block>& getChain() const;
    bool isValid() const;
};

#endif
