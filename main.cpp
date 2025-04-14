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
    std::cout << "6. Admin Login (for admin tasks)\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

void displayAdminMenu() {
    std::cout << "\n===== Admin Menu =====\n";
    std::cout << "1. Show Votes\n";
    std::cout << "2. Add Candidate\n";
    std::cout << "3. View All Voters\n";
    std::cout << "4. Exit Admin Mode\n";
    std::cout << "Enter your choice: ";
}

int main() {
    VoteManager vm;
    vm.loadFromFile();
    int choice;
    bool adminLoggedIn = false;

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
                std::string voterID, voterName, password;
                std::cout << "Enter Voter ID: ";
                std::getline(std::cin, voterID);
                std::cout << "Enter Voter Name: ";
                std::getline(std::cin, voterName);
                std::cout << "Set Password: ";
                std::cin >> password;
                std::cin.ignore();
                vm.registerVoter(voterID, voterName, password);
                break;
            }
            case 2: {
                std::string name;
                std::cout << "Enter Candidate Name: ";
                std::getline(std::cin, name);
                vm.registerCandidate(name);
                break;
            }
            case 3: {
                std::string voterID, password;
                int candidateIndex;
                std::cout << "Enter Voter ID: ";
                std::getline(std::cin, voterID);
                std::cout << "Enter Password: ";
                std::cin >> password;
                std::cin.ignore();
                vm.listCandidates();
                std::cout << "Enter candidate index (0-based): ";
                std::cin >> candidateIndex;
                std::cin.ignore();
                vm.castVote(voterID, password, candidateIndex);
                break;
            }
            case 4:
                vm.displayResults();
                break;
            case 5:
                vm.printBlockchain();
                break;
            case 6: {
                if (!adminLoggedIn) {
                    std::string adminPassword;
                    std::cout << "Enter Admin Password: ";
                    std::cin >> adminPassword;
                    std::cin.ignore();
                    adminLoggedIn = vm.loginAdmin(adminPassword);
                }

                if (adminLoggedIn) {
                    int adminChoice;
                    while (true) {
                        displayAdminMenu();
                        std::cin >> adminChoice;
                        std::cin.ignore();

                        switch (adminChoice) {
                            case 1:
                                vm.showVotes();
                                break;
                            case 2: {
                                std::string candidateName;
                                std::cout << "Enter new candidate name: ";
                                std::getline(std::cin, candidateName);
                                vm.addNewCandidate(candidateName);
                                break;
                            }
                            case 3:
                                vm.viewAllVoters();
                                break;
                            case 4:
                                std::cout << "Exiting admin mode...\n";
                                adminLoggedIn = false;
                                break;
                            default:
                                std::cout << "Invalid choice. Please try again.\n";
                        }

                        if (!adminLoggedIn) break;
                    }
                }
                break;
            }
            case 7:
                vm.saveToFile();
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}
