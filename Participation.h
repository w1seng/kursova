#ifndef PARTICIPATION_H
#define PARTICIPATION_H

#include "Athlete.h"
#include "Competition.h"

class Participation {
private:
    Athlete* athlete;
    Competition* competition;
    int place;

public:
    static vector<Participation*> allParticipations;
    Participation(Athlete* athlete, Competition* competition, int place);
    Athlete* getAthlete() const;
    Competition* getCompetition() const;
    int getPlace() const;
    void displayInfo() const;
    static const vector<Participation*>& getAllParticipations();
};

#endif
