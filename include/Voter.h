#ifndef VOTER_H
#define VOTER_H

#include <string>

class Voter {
private:
    std::string voterID;
    std::string name;
    bool hasVoted;
    std::size_t passwordHash;

public:
    Voter(const std::string& id, const std::string& name, const std::string& password);
    Voter() = default;

    bool getHasVoted() const;
    void setHasVoted(bool value);

    std::string getID() const;
    std::string getName() const;

    bool verifyPassword(const std::string& password) const;

    std::string serialize() const;
    void deserialize(const std::string& line);
};

#endif
