#ifndef SPORTSCLUB_H
#define SPORTSCLUB_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class SportsClub {
private:
    int id;
    string name;
    string contactInfo;

public:
    static vector<SportsClub*> allSportsClubs;
    SportsClub(int id, const string& name, const string& contactInfo);
    void displayInfo() const;
    string getName() const;
    int getId() const;
    static const vector<SportsClub*>& getAllSportsClubs();
    static SportsClub* findById(int id);
    string getContactInfo() const;
};

#endif
