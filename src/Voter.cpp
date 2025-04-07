// Voter.cpp
#include "../include/Voter.h"

Voter::Voter(const std::string& id, const std::string& name, const std::string& password)
    : voterID(id), name(name), hasVoted(false) {
        passwordHash = std::hash<std::string>{}(password); // Hash the password for storage
    }

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

bool Voter::verifyPassword(const std::string& inputPassword) const { 
    return std::hash<std::string>{}(inputPassword) == passwordHash; }