#include "Athlete.h"

vector<Athlete*> Athlete::allAthletes;

Athlete::Athlete(int id, const string& name, SportsClub* club)
    : id(id), name(name), club(club) {
    allAthletes.push_back(this);
}

void Athlete::addSport(Sport* sport, int rank) {
    sports[sport] = rank;
}

void Athlete::addCoach(Sport* sport, Coach* coach) {
    coaches[sport].push_back(coach);
}

void Athlete::displayInfo() const {
    cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<< endl;
    cout << "Спортсмен: " << name << endl;
    if (club) club->displayInfo();
    cout << "Види спорту та розряди:\n";
    for (const auto& pair : sports) {
        cout << "  " << pair.first->getName() << " (Розряд: " << pair.second << ")\n";
    }
    cout << "Тренери:\n";
    for (const auto& pair : coaches) {
        cout << "  " << pair.first->getName() << ": ";
        for (const auto& coach : pair.second) {
            cout << coach->getName() << " ";
        }
        cout << endl;
    }
}


int Athlete::getId() const {
    return id;
}

string Athlete::getName() const {
    return name;
}

SportsClub* Athlete::getClub() const {
    return club;
}

const map<Sport*, int>& Athlete::getSports() const {
    return sports;
}

const map<Sport*, vector<Coach*>>& Athlete::getCoaches() const {
    return coaches;
}

const vector<Athlete*>& Athlete::getAllAthletes() {
    return allAthletes;
}

Athlete* Athlete::findById(int id) {

    for (Athlete* athlete : Athlete::allAthletes) {
        if (athlete->getId() == id) {
            return athlete;
        }
    }
    return nullptr;
}

