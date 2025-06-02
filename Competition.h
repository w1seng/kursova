#ifndef COMPETITION_H
#define COMPETITION_H

#include <string>
#include <vector>
#include <iostream>
#include "SportFacility.h"
#include "Sport.h"

using namespace std;

class Competition {
private:
    int id;
    string name;
    string date;
    string organizer;
    SportsFacility* facility;
    Sport* sport;

public:
    static vector<Competition*> allCompetitions;
    Competition(int id, const string& name, const string& date, const string& organizer, SportsFacility* facility, Sport* sport);
    SportsFacility* getFacility() const;
    Sport* getSport() const;
    string getDate() const;
    string getName() const;
    int getId() const;
    string getOrganizer() const;
    void displayInfo() const;
    static const vector<Competition*>& getAllCompetitions();
    static Competition* findById(int id);
};

#endif
