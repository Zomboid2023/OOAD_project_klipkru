#include "../include/Candidate.h"
#include <sstream>
#include <iostream>

Candidate::Candidate(const std::string& name) : name(name), voteCount(0) {}

std::string Candidate::getName() const { return name; }
int Candidate::getVoteCount() const { return voteCount; }
void Candidate::addVote() { 
    std::cout << "Vote added to candidate: " << name << std::endl;
    voteCount++; 
}

std::string Candidate::serialize() const {
    return name + "," + std::to_string(voteCount);
}

void Candidate::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::getline(ss, name, ',');
    std::getline(ss, token, ',');
    voteCount = std::stoi(token);
}
