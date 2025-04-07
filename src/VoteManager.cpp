#include "../include/VoteManager.h"
#include <iostream>

void VoteManager::registerVoter(const std::string& id, const std::string& name) {
    if (voters.find(id) == voters.end()) {
        voters.emplace(id, Voter(id, name));  // ✅ No default constructor needed
    }
}

bool VoteManager::registerCandidate(const std::string& name) {
    for (const auto& c : candidates) {
        if (c.getName() == name) {
            std::cout << "Candidate name already exists.\n";
            return false;
        }
    }
    candidates.push_back(Candidate(name));
    return true;
}

void VoteManager::listCandidates() const {
    std::cout << "Available Candidates:\n";
    for (size_t i = 0; i < candidates.size(); ++i) {
        std::cout << i << ": " << candidates[i].getName() << "\n";
    }
}


void VoteManager::castVote(const std::string& voterID, int candidateIndex) {
    auto it = voters.find(voterID);
    if (it == voters.end()) {
        std::cout << "Voter not registered.\n";
        return;
    }

    if (it->second.getHasVoted()) {
        std::cout << "Voter has already voted.\n";
        return;
    }

    if (candidateIndex < 0 || candidateIndex >= candidates.size()) {
        std::cout << "Invalid candidate index.\n";
        return;
    }

    // ✅ Use Candidate class method
    candidates[candidateIndex].addVote();

    it->second.setHasVoted(true);

    // ✅ Use Candidate class method
    blockchain.addBlock("Voter ID: " + voterID + " voted for " + candidates[candidateIndex].getName());

    std::cout << "Vote cast successfully.\n";
}

void VoteManager::displayResults() const {
    std::cout << "\nElection Results:\n";
    for (const auto& candidate : candidates) {
        std::cout << candidate.getName() << ": " << candidate.getVoteCount() << " votes\n";
    }
}

void VoteManager::printBlockchain() const {
    std::cout << "\nBlockchain Ledger:\n";
    for (const auto& block : blockchain.getChain()) {
        std::cout << "Index: " << block.index << ", Data: " << block.data
                  << ", Hash: " << block.hash << ", PrevHash: " << block.prevHash << "\n";
    }
}
