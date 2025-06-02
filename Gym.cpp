#include "Gym.h"

Gym::Gym(int id, const string& name, const string& address, int numMachines)
    : SportsFacility(id, name, address), numMachines(numMachines) {}

void Gym::displayInfo() const {
    SportsFacility::displayInfo();
    cout << "Тип: Тренажерний зал\nКількість тренажерів: " << numMachines << "\n";
}

int Gym::getNumMachines() const {
    return numMachines;
}