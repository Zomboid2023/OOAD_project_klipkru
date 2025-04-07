#ifndef VOTER_H
#define VOTER_H

#include <string>

// Voter.h
class Voter {
    private:
        std::string voterID;
        std::string name;
        bool hasVoted;
    
    public:
        Voter(const std::string& id, const std::string& name);
    
        // ✅ Add these
        bool getHasVoted() const;
        void setHasVoted(bool value);
    
        std::string getID() const;
        std::string getName() const;
    };
    
    

#endif
