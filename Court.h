#ifndef COURT_H
#define COURT_H

#include "SportFacility.h"

class Court : public SportsFacility {
private:
    string surfaceType;

public:
    Court(int id, const string& name, const string& address, const string& surfaceType);
    void displayInfo() const override;
    string getSurfaceType() const;
};

#endif
