#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>

class Candidate {
private:
    std::string name;
    int voteCount;

public:
    Candidate(const std::string& name);
    Candidate() = default;

    std::string getName() const;
    int getVoteCount() const;
    void addVote();

    std::string serialize() const;
    void deserialize(const std::string& line);
};

#endif
