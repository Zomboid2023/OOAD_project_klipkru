// Voter.cpp
#include "../include/Voter.h"

Voter::Voter(const std::string& id, const std::string& name)
    : voterID(id), name(name), hasVoted(false) {}

bool Voter::getHasVoted() const {
    return hasVoted;
}

void Voter::setHasVoted(bool value) {
    hasVoted = value;
}

std::string Voter::getID() const {
    return voterID;
}

std::string Voter::getName() const {
    return name;
}
