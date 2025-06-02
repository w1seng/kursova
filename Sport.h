#ifndef SPORT_H
#define SPORT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Sport {
private:
    int id;
    string name;

public:
    static vector<Sport*> allSports;
    Sport(int id, const string& name);
    string getName() const;
    int getId() const;
    void displayInfo() const;
    static const vector<Sport*>& getAllSports();
    static Sport* findById(int id);
};

#endif
