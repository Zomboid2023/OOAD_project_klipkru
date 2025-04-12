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
    std::cout << "3. Exit Admin Mode\n";
    std::cout << "Enter your choice: ";
}

int main() {
    VoteManager vm;
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
                std::string voterID, voterName;
                std::cout << "Enter Voter ID: ";
                std::getline(std::cin, voterID);
                std::cout << "Enter Voter Name: ";
                std::getline(std::cin, voterName);
                std::string password;
                std::cout << "Set Password: "; 
                std::cin >> password;
                vm.registerVoter(voterID, voterName, password);
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
                std::string voterID, password;
                int candidateIndex;
                std::cout << "Enter Voter ID: ";
                std::getline(std::cin, voterID);
                std::cout << "Enter Password: "; 
                std::cin >> password;
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
                    std::cin.ignore(); // Clear the input buffer
                    adminLoggedIn = vm.loginAdmin(adminPassword);
                }

                // If admin is logged in
                if (adminLoggedIn) {
                    int adminChoice;
                    while (true) {
                        displayAdminMenu();
                        std::cin >> adminChoice;
                        std::cin.ignore(); // Clear the input buffer

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
                                std::cout << "Exiting admin mode...\n";
                                adminLoggedIn = false;
                                break;
                            default:
                                std::cout << "Invalid choice. Please try again.\n";
                        }

                        if (!adminLoggedIn) {
                            break; // Exit the loop when admin logs out
                        }
                    }
                }
                break;
            }
            case 7:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}
