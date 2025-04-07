#ifndef BLOCK_H
#define BLOCK_H

#include <string>

class Block {
public:
    int index;
    std::string data;
    std::string prevHash;
    std::string hash;

    Block(int idx, const std::string& data, const std::string& prevHash);
    std::string calculateHash() const;
};

#endif
