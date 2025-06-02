#ifndef GYM_H
#define GYM_H

#include "SportFacility.h"

class Gym : public SportsFacility {
private:
    int numMachines;

public:
    Gym(int id, const string& name, const string& address, int numMachines);
    void displayInfo() const override;
    int getNumMachines() const;
};

#endif
