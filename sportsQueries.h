#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

class SportsFacility;
class Stadium;
class Court;
class SportHall;
class SwimmingPool;
class Gym;
class Sport;
class Athlete;
class Coach;
class Competition;
class Participation;
class SportsClub;

class SportsQueries {
public:
    static vector<SportsFacility*> filterFacilities();
    static vector<Athlete*> getAthletesBySportAndRank();
    static vector<Athlete*> getAthletesByCoachAndRank();
    static vector<Athlete*> getAthletesWithMultipleSports();
    static vector<Coach*> getCoachesByAthlete();
    static vector<Competition*> getCompetitionsByDateAndOrganizer();
    static vector<Competition*> getCompetitionsByFacilityAndSport();
    static map<SportsClub*, int> getClubsAndAthleteCounts();
    static vector<Coach*> getCoachesBySport();
    static vector<Athlete*> getAthletesWithoutParticipation();
    static map<string, int> getOrganizersAndCompetitionCounts();
    static map<SportsFacility*, vector<string>> getFacilitiesAndCompetitionDates();

};
