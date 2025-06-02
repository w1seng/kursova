#include "SwimmingPool.h"

SwimmingPool::SwimmingPool(int id, const string& name, const string& address, float length)
    : SportsFacility(id, name, address), length(length) {}

void SwimmingPool::displayInfo() const {
    SportsFacility::displayInfo();
    cout << "Тип: Басейн\nДовжина: " << length << " м\n";
}

int SwimmingPool::getLength() const {
    return length;
}