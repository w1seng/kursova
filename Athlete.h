#ifndef ATHLETE_H
#define ATHLETE_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "Coach.h"
#include "SportsClub.h"

using namespace std;

class Athlete {
private:
    int id;
    string name;
    SportsClub* club;
    map<Sport*, int> sports;
    map<Sport*, vector<Coach*>> coaches;

public:
    static vector<Athlete*> allAthletes;
    Athlete(int id, const string& name, SportsClub* club);
    void addSport(Sport* sport, int rank);
    void addCoach(Sport* sport, Coach* coach);
    void displayInfo() const;
    SportsClub* getClub() const;
    string getName() const;
    int getId() const;
    const map<Sport*, int>& getSports() const;
    const map<Sport*, vector<Coach*>>& getCoaches() const;
    static const vector<Athlete*>& getAllAthletes();
    static Athlete* findById(int id);
};

#endif
