#include "Stadium.h"

Stadium::Stadium(int id, const string& name, const string& address, int capacity)
    : SportsFacility(id, name, address), capacity(capacity) {}

void Stadium::displayInfo() const {
    SportsFacility::displayInfo();
    cout << "Тип: Стадіон\nМісткість: " << capacity << " глядачів\n";
}

int Stadium::getCapacity() const {
    return capacity;
}