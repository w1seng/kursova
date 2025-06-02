#ifndef SPORTHALL_H
#define SPORTHALL_H

#include "SportFacility.h"

class SportHall : public SportsFacility {
private:
    float area;

public:
    SportHall(int id, const string& name, const string& address, float area);
    void displayInfo() const override;
    float getArea() const;
};

#endif
