#include "Competition.h"

vector<Competition*> Competition::allCompetitions;

Competition::Competition(int id, const string& name, const string& date, const string& organizer, SportsFacility* facility, Sport* sport)
    : id(id), name(name), date(date), organizer(organizer), facility(facility), sport(sport) {
    allCompetitions.push_back(this);
}

void Competition::displayInfo() const {
    cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<< endl;
    cout << "Змагання: " << name << "\nДата: " << date << "\nОрганізатор: " << organizer << endl;
    if (facility) facility->displayInfo();
    if (sport) cout << "Вид спорту: " << sport->getName() << endl;
}

int Competition::getId() const { return id; }
string Competition::getName() const { return name; }
string Competition::getDate() const { return date; }
string Competition::getOrganizer() const { return organizer; }
Sport* Competition::getSport() const { return sport; }
SportsFacility* Competition::getFacility() const { return facility; }

const vector<Competition*>& Competition::getAllCompetitions() {
    return allCompetitions;
}

Competition* Competition::findById(int id) {
    for (Competition* competition : Competition::allCompetitions) {
        if (competition->getId() == id) {
            return competition;
        }
    }
    return nullptr;
}