#ifndef SWIMMINGPOOL_H
#define SWIMMINGPOOL_H

#include "SportFacility.h"

class SwimmingPool : public SportsFacility {
private:
    float length;

public:
    SwimmingPool(int id, const string& name, const string& address, float length);
    void displayInfo() const override;
    int getLength() const;
};

#endif
