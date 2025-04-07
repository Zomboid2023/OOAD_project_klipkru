#include "../include/Candidate.h"

Candidate::Candidate(const std::string& name) : name(name), voteCount(0) {}

std::string Candidate::getName() const {
    return name;
}

int Candidate::getVoteCount() const {
    return voteCount;
}

void Candidate::addVote() {
    voteCount++;
}
