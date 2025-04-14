#include "../include/VoteManager.h"
#include <iostream>
#include <sstream>
#include <fstream>

// Constructor
VoteManager::VoteManager() {
    admin = new Admin("admin", "admin123");
}

// Destructor
VoteManager::~VoteManager() {
    delete admin;
}

bool VoteManager::loginAdmin(const std::string& password) {
    if (admin && admin->verifyPassword(password)) {
        std::cout << "Admin login successful.\n";
        return true;
    }
    std::cout << "Admin login failed.\n";
    return false;
}

void VoteManager::registerVoter(const std::string& id, const std::string& name, const std::string& password) {
    if (voters.find(id) == voters.end()) {
        voters.emplace(id, Voter(id, name, password));
        std::cout << "Voter registered.\n";
    } else {
        std::cout << "Voter ID already registered.\n";
    }
}

bool VoteManager::registerCandidate(const std::string& name) {
    for (const auto& c : candidates) {
        if (c.getName() == name) {
            std::cout << "Candidate already exists.\n";
            return false;
        }
    }
    candidates.emplace_back(name);
    std::cout << "Candidate registered.\n";
    return true;
}

void VoteManager::castVote(const std::string& voterID, const std::string& password, int candidateIndex) {
    auto it = voters.find(voterID);
    if (it == voters.end()) {
        std::cout << "Voter not registered.\n";
        return;
    }

    if (!it->second.verifyPassword(password)) {
        std::cout << "Authentication failed. Incorrect password.\n";
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

    // Candidate voting logic
    std::cout << "Casting vote for: " << candidates[candidateIndex].getName() << std::endl;

    // ✅ Use Candidate class method to add vote
    candidates[candidateIndex].addVote();

    // Mark voter as having voted
    it->second.setHasVoted(true);

    // Add voting transaction to blockchain
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
        std::cout << "Index: " << block.index
                  << ", Data: " << block.data
                  << ", Hash: " << block.hash
                  << ", PrevHash: " << block.prevHash << "\n";
    }
}

void VoteManager::listCandidates() const {
    if (candidates.empty()) {
        std::cout << "No candidates available.\n";
        return;
    }
    for (size_t i = 0; i < candidates.size(); ++i) {
        std::cout << "ID: " << i << ", Name: " << candidates[i].getName() << "\n";
    }
}


void VoteManager::showVotes() const {
    std::cout << "\nCurrent Votes:\n";
    for (const auto& candidate : candidates) {
        std::cout << candidate.getName() << ": " << candidate.getVoteCount() << " votes\n";
    }
}

void VoteManager::addNewCandidate(const std::string& name) {
    registerCandidate(name);
}

void VoteManager::viewAllVoters() const {
    std::cout << "\nRegistered Voters:\n";
    if (voters.empty()) {
        std::cout << "No voters registered.\n";
        return;
    }

    for (const auto& pair : voters) {
        const Voter& voter = pair.second;
        std::cout << "ID: " << voter.getID()
                  << ", Name: " << voter.getName()
                  << ", Has Voted: " << (voter.getHasVoted() ? "Yes" : "No") << "\n";
    }
}

void VoteManager::saveToFile() const {
    std::ofstream vfile("voters.txt");
    for (const auto& pair : voters)
        vfile << pair.second.serialize() << "\n";

    std::ofstream cfile("candidates.txt");
    for (const auto& c : candidates)
        cfile << c.serialize() << "\n";

    std::ofstream bfile("blockchain.txt");
    bfile << blockchain.serialize();
}

void VoteManager::loadFromFile() {
    std::ifstream vfile("voters.txt");
    std::string line;
    while (std::getline(vfile, line)) {
        Voter v;
        v.deserialize(line);
        voters[v.getID()] = v;
    }

    std::ifstream cfile("candidates.txt");
    while (std::getline(cfile, line)) {
        Candidate c;
        c.deserialize(line);
        candidates.push_back(c);
    }

    std::ifstream bfile("blockchain.txt");
    std::stringstream buffer;
    buffer << bfile.rdbuf();
    blockchain.deserialize(buffer.str());
}


std::vector<std::string> VoteManager::getCandidatesNames() const {
    std::vector<std::string> candidateNames;
    for (const auto& candidate : candidates) {
        candidateNames.push_back(candidate.getName());
    }
    return candidateNames;
}

