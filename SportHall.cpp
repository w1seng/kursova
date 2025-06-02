#include "SportHall.h"

SportHall::SportHall(int id, const string& name, const string& address, float area)
    : SportsFacility(id, name, address), area(area) {}

void SportHall::displayInfo() const {
    SportsFacility::displayInfo();
    cout << "Тип: Спортзал\nПлоща: " << area << " м²\n";
}

float SportHall::getArea() const {
    return area;
}