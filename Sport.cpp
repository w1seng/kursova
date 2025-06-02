#include "Sport.h"

vector<Sport*> Sport::allSports;

Sport::Sport(int id, const string& name) : id(id), name(name) {
    allSports.push_back(this);
}

string Sport::getName() const {
    return name;
}

int Sport::getId() const {
    return id;
}

void Sport::displayInfo() const {
    cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<< endl;
    cout << "Вид спорту: " << name << endl;
}

const vector<Sport*>& Sport::getAllSports() {
    return allSports;
}

Sport* Sport::findById(int id) {
    for (Sport* sport : Sport::allSports) {
        if (sport->getId() == id) {
            return sport;
        }
    }
    return nullptr;
}