#include "SportFacility.h"

vector<SportsFacility*> SportsFacility::allFacilities;

SportsFacility::SportsFacility(int id, const string& name, const string& address)
    : id(id), name(name), address(address) {
    allFacilities.push_back(this);
}

void SportsFacility::displayInfo() const {
    cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<< endl;
    cout << "ID: " << id << "\nНазва: " << name << "\nАдреса: " << address << endl;
}

const vector<SportsFacility*>& SportsFacility::getAllFacilities() {
    return allFacilities;
}

SportsFacility* SportsFacility::findById(int id) {
    for (SportsFacility* facility : SportsFacility::allFacilities) {
        if (facility->getId() == id) {
            return facility;
        }
    }
    return nullptr;
}