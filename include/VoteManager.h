#ifndef VOTEMANAGER_H
#define VOTEMANAGER_H

#include <vector>
#include <unordered_map>
#include "Voter.h"
#include "Candidate.h"
#include "Blockchain.h"

class VoteManager {
private:
    std::unordered_map<std::string, Voter> voters;
    std::vector<Candidate> candidates;
    Blockchain blockchain;

public:
    void registerVoter(const std::string& id, const std::string& name);
    bool registerCandidate(const std::string& name);
    void castVote(const std::string& voterID, int candidateIndex);
    void displayResults() const;
    void printBlockchain() const;
    void listCandidates() const;

};

#endif
