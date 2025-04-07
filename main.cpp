#include <iostream>
#include <limits>
#include "include/VoteManager.h"

void displayMenu() {
    std::cout << "\n===== Blockchain Voting System =====\n";
    std::cout << "1. Register Voter\n";
    std::cout << "2. Register Candidate\n";
    std::cout << "3. Cast Vote\n";
    std::cout << "4. View Election Results\n";
    std::cout << "5. View Blockchain Ledger\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    VoteManager vm;
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::string voterID, voterName;
                std::cout << "Enter Voter ID: ";
                std::getline(std::cin, voterID);
                std::cout << "Enter Voter Name: ";
                std::getline(std::cin, voterName);
                vm.registerVoter(voterID, voterName);
                std::cout << "Voter registered.\n";
                break;
            }
            case 2: {
                std::string name;
                std::cout << "Enter Candidate Name: ";
                std::getline(std::cin, name);
                if (vm.registerCandidate(name))
                    std::cout << "Candidate registered.\n";
                break;
            }
            case 3: {
                std::string voterID;
                int candidateIndex;
                std::cout << "Enter Voter ID: ";
                std::getline(std::cin, voterID);
                vm.listCandidates();
                std::cout << "Enter candidate index (0-based): ";
                std::cin >> candidateIndex;
                std::cin.ignore();
                vm.castVote(voterID, candidateIndex);
                break;
            }
            case 4:
                vm.displayResults();
                break;
            case 5:
                vm.printBlockchain();
                break;
            case 6:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}
