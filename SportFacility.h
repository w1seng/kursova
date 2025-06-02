#ifndef SPORTS_FACILITY_H
#define SPORTS_FACILITY_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SportsFacility {
protected:
    int id;
    string name;
    string address;

public:
    static vector<SportsFacility*> allFacilities;
    SportsFacility(int id, const string& name, const string& address);
    int getId() const { return id; }
    virtual void displayInfo() const;
    virtual ~SportsFacility() = default;
    static SportsFacility* findById(int id);
    static const vector<SportsFacility*>& getAllFacilities();
    string getName() const { return name; }
    string getAddress() const { return address; }
};

#endif
