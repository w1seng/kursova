#ifndef STADIUM_H
#define STADIUM_H

#include "SportFacility.h"

class Stadium : public SportsFacility {
private:
    int capacity;

public:
    Stadium(int id, const string& name, const string& address, int capacity);
    void displayInfo() const override;
    int getCapacity() const;
};

#endif
