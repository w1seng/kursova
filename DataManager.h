#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "User.h"
#include <string>

class DataManager {
private:
    User* user;

public:
    DataManager(User* user);
    void saveData(const std::string& filename);
    void loadData(const std::string& filename);
    void add_Athlete();
    void add_Sport();
    void add_Coach();
    void add_SportsClub();
    void add_Competition();
    void add_SportsFacility();
    void add_Participation(); 
    
    void showMenu();
};

#endif
