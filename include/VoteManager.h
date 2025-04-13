#ifndef VOTEMANAGER_H
#define VOTEMANAGER_H

#include <vector>
#include <unordered_map>
#include "Voter.h"
#include "Candidate.h"
#include "Blockchain.h"
#include "Admin.h" // Include Admin header

class VoteManager {
private:
    std::unordered_map<std::string, Voter> voters;
    std::vector<Candidate> candidates;
    Blockchain blockchain;
    Admin* admin; // Admin object for checking if the current user is an admin

public:
    VoteManager();
    bool loginAdmin(const std::string& password); // Admin login function
    void registerVoter(const std::string& id, const std::string& name, const std::string& password);
    bool registerCandidate(const std::string& name);
    void castVote(const std::string& voterID, const std::string& password, int candidateIndex);
    void displayResults() const;
    void printBlockchain() const;
    void listCandidates() const;

    // Admin-only functionality
    void showVotes() const;  // Show all votes for each candidate
    void addNewCandidate(const std::string& name); // Add candidate (only for admin)
    void viewAllVoters() const;

};

#endif