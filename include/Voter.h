#ifndef VOTER_H
#define VOTER_H

#include <string>

// Voter.h
class Voter {
    private:
        std::string voterID;
        std::string name;
        bool hasVoted;
        private: std::size_t passwordHash;
    
    public:
        Voter(const std::string& id, const std::string& name, const std::string& password);

        // ✅ Add these
        bool getHasVoted() const;
        void setHasVoted(bool value);
    
        std::string getID() const;
        std::string getName() const;

        bool verifyPassword(const std::string& password) const;
    };
    
    

#endif
