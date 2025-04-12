#include "../include/Admin.h"
#include <functional>

Admin::Admin(const std::string& id, const std::string& password)
    : adminID(id) {
        passwordHash = std::hash<std::string>{}(password); // Store hashed password for security
    }

bool Admin::verifyPassword(const std::string& inputPassword) const {
    return std::hash<std::string>{}(inputPassword) == passwordHash;
}
