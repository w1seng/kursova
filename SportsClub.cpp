#include "SportsClub.h"

vector<SportsClub*> SportsClub::allSportsClubs;

SportsClub::SportsClub(int id, const string& name, const string& contactInfo)
    : id(id), name(name), contactInfo(contactInfo) {
    allSportsClubs.push_back(this);
}

void SportsClub::displayInfo() const {
    cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<< endl;
    cout << "Клуб: " << name << "\nКонтакти: " << contactInfo << endl;
}

string SportsClub::getName() const {
    return name;
}

int SportsClub::getId() const {
    return id;
}

const vector<SportsClub*>& SportsClub::getAllSportsClubs() {
    return allSportsClubs;
}

SportsClub* SportsClub::findById(int id) {
    for (SportsClub* club : SportsClub::allSportsClubs) {
        if (club->getId() == id) {
            return club;
        }
    }
    return nullptr;
}

string SportsClub::getContactInfo() const {
    return contactInfo;
}