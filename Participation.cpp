#include "Participation.h"

vector<Participation*> Participation::allParticipations;

Participation::Participation(Athlete* athlete, Competition* competition, int place)
    : athlete(athlete), competition(competition), place(place) {
    allParticipations.push_back(this);
}

Athlete* Participation::getAthlete() const {
    return athlete;
}

Competition* Participation::getCompetition() const {
    return competition;
}

int Participation::getPlace() const {
    return place;
}

const vector<Participation*>& Participation::getAllParticipations() {
    return allParticipations;
}

void Participation::displayInfo() const {
    cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<< endl;
    if (athlete && competition) {
        athlete->displayInfo();
        competition->displayInfo();
        cout << "Місце: " << place << endl;
    }
}