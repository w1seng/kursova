#ifndef USER_H
#define USER_H

#include <string>

struct User {
    std::string username;
    std::string password;
    int accessLevel; 
    
    int getAccessLevel() const {
        return accessLevel;
    }
};

bool loadAdminCredentials(std::string& adminLogin, std::string& adminPassword);
User showLoginMenu();

#endif
