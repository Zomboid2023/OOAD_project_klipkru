#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class Admin {
private:
    std::string adminID;
    std::size_t passwordHash;

public:
    Admin(const std::string& id, const std::string& password);
    bool verifyPassword(const std::string& inputPassword) const;
};

#endif
