#include <iostream>
#include <limits>
#include "include/VoteManager.h"
#include <iostream>
using namespace std;

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

int main(int argc, char* argv[]) {
    VoteManager vm;
    vm.loadFromFile();

    // cout<<argc<<endl;
    // --- Command Line Interface Support ---
    if (argc > 1) {
        std::string command = argv[1];

        if (command == "register_voter" && argc == 5) {
            std::string voterID = argv[2];
            std::string voterName = argv[3];
            std::string password = argv[4];
            vm.registerVoter(voterID, voterName, password);
        }
        else if (command == "register_candidate" && argc == 3) {
            std::string name = argv[2];
            vm.registerCandidate(name);
        }
        else if (command == "list_candidates") {
            vm.listCandidates(); // Make sure this function is defined in VoteManager
        }        
        else if (command == "cast_vote" && argc == 5) {
            std::string voterID = argv[2];
            std::string password = argv[3];
            std::string candidateIndexStr = argv[4];

            try {
                int candidateIndex = std::stoi(candidateIndexStr);
                vm.castVote(voterID, password, candidateIndex);
            } catch (const std::invalid_argument& e) {
                std::cout << "Invalid candidate index: " << candidateIndexStr << std::endl;
                std::cout << "Please enter a valid number for the candidate index.\n";
            } catch (const std::out_of_range& e) {
                std::cout << "Candidate index out of range.\n";
            }
        }
        else if (command == "view_voters") {
            vm.viewAllVoters();
        }
        else if (command == "view_results") {
            vm.displayResults();
        }
        else if (command == "view_ledger") {
            vm.printBlockchain();
        }
        else if (command == "login_admin" && argc == 3) {
            std::string password = argv[2];
            if (vm.loginAdmin(password)) {
                std::cout << "Admin login successful.\n";
            } else {
                std::cout << "Admin login failed.\n";
            }
        }
        else {
            std::cout << "Invalid command or arguments.\n";
            std::cout << "Example: voting_app.exe register_voter 101 Alice securepass\n";
        }

        vm.saveToFile();
        return 0;
    }

    // --- Interactive Menu ---
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
