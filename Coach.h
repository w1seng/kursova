#ifndef COACH_H
#define COACH_H

#include <string>
#include <vector>
#include "Sport.h"

using namespace std;

class Coach {
private:
    int id;
    string name;
    Sport* sport;

public:
    static vector<Coach*> allCoaches;
    Coach(int id, const string& name, Sport* sport);
    void displayInfo() const;
    int getId() const;
    string getName() const;
    Sport* getSport() const;
    static const vector<Coach*>& getAllCoaches();
    static Coach* findById(int id);
};

#endif
