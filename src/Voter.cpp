#include "../include/Voter.h"
#include <sstream>
#include <functional>

Voter::Voter(const std::string& id, const std::string& name, const std::string& password)
    : voterID(id), name(name), hasVoted(false) {
    passwordHash = std::hash<std::string>{}(password);
}

bool Voter::getHasVoted() const { return hasVoted; }
void Voter::setHasVoted(bool value) { hasVoted = value; }

std::string Voter::getID() const { return voterID; }
std::string Voter::getName() const { return name; }

bool Voter::verifyPassword(const std::string& password) const {
    return passwordHash == std::hash<std::string>{}(password);
}

std::string Voter::serialize() const {
    return voterID + "," + name + "," + (hasVoted ? "1" : "0") + "," + std::to_string(passwordHash);
}

void Voter::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::getline(ss, voterID, ',');
    std::getline(ss, name, ',');
    std::getline(ss, token, ',');
    hasVoted = (token == "1");
    std::getline(ss, token, ',');
    passwordHash = std::stoull(token);
}
