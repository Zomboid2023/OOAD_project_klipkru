#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>

// Candidate.h
// Candidate.h
class Candidate {
    private:
        std::string name;
        int voteCount;
    
    public:
        Candidate(const std::string& name);  // Just declare here
        std::string getName() const;
        int getVoteCount() const;
        void addVote();
    };
        

#endif
