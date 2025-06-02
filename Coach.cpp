#include "Coach.h"

vector<Coach*> Coach::allCoaches;

Coach::Coach(int id, const string& name, Sport* sport)
    : id(id), name(name), sport(sport) {
    allCoaches.push_back(this);
}

void Coach::displayInfo() const {
    cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<< endl;
    cout << "Тренер: " << name << "\nВид спорту: " << (sport ? sport->getName() : "Невідомо") << endl;
}

int Coach::getId() const {
    return id;
}

string Coach::getName() const {
    return name;
}

Sport* Coach::getSport() const {
    return sport;
}

const vector<Coach*>& Coach::getAllCoaches() {
    return allCoaches;
}

Coach* Coach::findById(int id) {
    for (Coach* coach : Coach::allCoaches) {
        if (coach->getId() == id) {
            return coach;
        }
    }
    return nullptr;
}