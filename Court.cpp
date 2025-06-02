#include "Court.h"

Court::Court(int id, const string& name, const string& address, const string& surfaceType)
    : SportsFacility(id, name, address), surfaceType(surfaceType) {}

void Court::displayInfo() const {
    SportsFacility::displayInfo();
    cout << "Тип: Корт\nПокриття: " << surfaceType << "\n";
}

string Court::getSurfaceType() const {
    return surfaceType;
}