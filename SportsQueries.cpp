#include "SportsQueries.h"
#include "SportFacility.h"
#include "Stadium.h"
#include "Court.h"
#include "SportHall.h"
#include "SwimmingPool.h"
#include "Gym.h"
#include "Athlete.h"
#include "Coach.h"
#include "Sport.h"
#include "Competition.h"
#include "Participation.h"
#include "SportsClub.h"
#define INT_MAX 4

vector<SportsFacility*> SportsQueries::filterFacilities() {
    cout << "Доступні типи спортивних споруд:\n";
                cout << "1 - Стадіон\n";
                cout << "2 - Корт\n";
                cout << "3 - Спортзал\n";
                cout << "4 - Басейн\n";
                cout << "5 - Тренажерний зал\n";
                cout << "0 - Вихід\n";
                cout << "Оберіть тип споруди: ";
                int subChoice;
                cin >> subChoice;

                if (subChoice == 0) {
                    return {}; 
                }

                string type;
                map<string, string> criteria;

                switch (subChoice) {
                    case 1:
                    
                        type = "Stadium";
                        cout << "Фільтрувати за мінімальною місткістю? (1 - так, 0 - ні): ";
                        int filterCapacity;
                        cin >> filterCapacity;
                        if (filterCapacity) {
                            cout << "Введіть мінімальну місткість: ";
                            int minCapacity;
                            cin >> minCapacity;
                            criteria["minCapacity"] = to_string(minCapacity);
                        }
                        break;
                    case 2:
                        type = "Court";
                        cout << "Фільтрувати за типом покриття? (1 - так, 0 - ні): ";
                        int filterSurface;
                        cin >> filterSurface;
                        if (filterSurface) {
                            cout << "Введіть тип покриття (Clay,Hard): ";
                            string surfaceType;
                            cin >> surfaceType;
                            criteria["surfaceType"] = surfaceType;
                        }
                        break;
                    case 3:
                        type = "sporthall";
                        cout << "Фільтрувати за мінімальною площею? (1 - так, 0 - ні): ";
                        int filterArea;
                        cin >> filterArea;
                        if (filterArea) {
                            cout << "Введіть мінімальну площу: ";
                            float minArea;
                            cin >> minArea;
                            criteria["minArea"] = to_string(minArea);
                        }
                        break;
                    case 4:
                        type = "swimmingpool";
                        cout << "Фільтрувати за мінімальною довжиною? (1 - так, 0 - ні): ";
                        int filterLength;
                        cin >> filterLength;
                        if (filterLength) {
                            cout << "Введіть мінімальну довжину басейну: ";
                            float minLength;
                            cin >> minLength;
                            criteria["minLength"] = to_string(minLength);
                        }
                        break;
                    case 5:
                        type = "gym";
                        cout << "Фільтрувати за мінімальною кількістю тренажерів? (1 - так, 0 - ні): ";
                        int filterMachines;
                        cin >> filterMachines;
                        if (filterMachines) {
                            cout << "Введіть мінімальну кількість тренажерів: ";
                            int minMachines;
                            cin >> minMachines;
                            criteria["minMachines"] = to_string(minMachines);
                        }
                        break;
                    default:
                        cout << "Невірний вибір. Спробуйте ще раз.\n";
                        return {};
                }

    vector<SportsFacility*> result;

    for (const auto& facility : SportsFacility::getAllFacilities()) {
        if (type == "Stadium") {
            Stadium* stadium = dynamic_cast<Stadium*>(facility);
            if (stadium) {
                if (criteria.empty() || (criteria.count("minCapacity") && stadium->getCapacity() >= stoi(criteria.at("minCapacity")))) {
                    result.push_back(stadium);
                }
            }
        } else if (type == "Court") {
            Court* court = dynamic_cast<Court*>(facility);
            if (court) {
                if (criteria.empty() || (criteria.count("surfaceType") && court->getSurfaceType() == criteria.at("surfaceType"))) {
                    result.push_back(court);
                }
            }
        } else if (type == "sporthall") {
            SportHall* hall = dynamic_cast<SportHall*>(facility);
            if (hall) {
                if (criteria.empty() || (criteria.count("minArea") && hall->getArea() >= stof(criteria.at("minArea")))) {
                    result.push_back(hall);
                }
            }
        } else if (type == "swimmingpool") {
            SwimmingPool* pool = dynamic_cast<SwimmingPool*>(facility);
            if (pool) {
                if (criteria.empty() || (criteria.count("minLength") && pool->getLength() >= stof(criteria.at("minLength")))) {
                    result.push_back(pool);
                }
            }
        } else if (type == "gym") {
            Gym* gymFacility = dynamic_cast<Gym*>(facility);
            if (gymFacility) {
                if (criteria.empty() || (criteria.count("minMachines") && gymFacility->getNumMachines() >= stoi(criteria.at("minMachines")))) {
                    result.push_back(gymFacility);
                }
            }
        } else if (type.empty()) {
            result.push_back(facility);
        }
    }

    return result;
}

vector<Athlete*> SportsQueries::getAthletesBySportAndRank() { 

    
                cout << "Доступні види спорту:\n";
                for (const auto& sport : Sport::getAllSports()) { 
                    cout << sport->getId() << " - " << sport->getName() << endl;
                }
            
                cout << "Введіть ID виду спорту: ";
                int sportId;
                cin >> sportId;
            
                cout << "Введіть мінімальний розряд (0 для пропуску): ";
                int minRank;
                cin >> minRank;
                if (minRank == 0){
                    minRank = INT_MAX; 
                }
                
                Sport* selectedSport = nullptr;
                for (const auto& sport : Sport::getAllSports()) { 
                    if (sport->getId() == sportId) {
                        selectedSport = sport;
                        break;
                    }
                }
            
                if (!selectedSport) {
                    cout << "Вид спорту не знайдено.\n";
                    return {};
                }

    vector<Athlete*> result;

    for (const auto& athlete : Athlete::getAllAthletes()) {
        const auto& sports = athlete->getSports();
        auto it = sports.find(selectedSport);
        if (it != sports.end() && it->second <= minRank) {
            result.push_back(athlete);
        }
    }

    return result;
}

vector<Athlete*> SportsQueries::getAthletesByCoachAndRank() { 
    cout << "Доступні тренери:\n";
                const auto& allCoaches = Coach::getAllCoaches(); 
                for (size_t i = 0; i < allCoaches.size(); ++i) {
                    cout << i + 1 << " - " << allCoaches[i]->getName() << "-" << allCoaches[i]->getSport()->getName() << endl;
                }
            
                cout << "Введіть номер тренера: ";
                int coachIndex;
                cin >> coachIndex;
            
                if (coachIndex < 1 || coachIndex > allCoaches.size()) {
                    cout << "Невірний вибір тренера.\n";
                    return {};
                }
            
                Coach* selectedCoach = allCoaches[coachIndex - 1];
            
                cout << "Введіть мінімальний розряд (0 для пропуску): ";
                int minRank;
                cin >> minRank;
                if (minRank == 0){
                    minRank = INT_MAX; 
                }
                
    vector<Athlete*> result;

    for (const auto& athlete : Athlete::getAllAthletes()) {
        const auto& sports = athlete->getSports();
        const auto& coaches = athlete->getCoaches();

        for (auto it = coaches.begin(); it != coaches.end(); ++it) {
            Sport* sport = it->first;
            const vector<Coach*>& coachList = it->second;

            if (find(coachList.begin(), coachList.end(), selectedCoach) != coachList.end()) {
                auto sportIt = sports.find(sport);
                if (sportIt != sports.end() && sportIt->second <= minRank) {
                    result.push_back(athlete);
                    break;
                }
            }
        }
    }

    return result;
}

vector<Athlete*> SportsQueries::getAthletesWithMultipleSports() { 
    

    vector<Athlete*> result;

    for (const auto& athlete : Athlete::getAllAthletes()) {
        if (athlete->getSports().size() > 1) {
            result.push_back(athlete);
        }
    }

    return result;
}

vector<Coach*> SportsQueries::getCoachesByAthlete() { 
    cout << "Доступні спортсмени:\n";
                const auto& allAthletes = Athlete::getAllAthletes(); 
                for (size_t i = 0; i < allAthletes.size(); ++i) {
                    cout << i + 1 << " - " << allAthletes[i]->getName() << endl;
                }
            
                cout << "Введіть номер спортсмена: ";
                int athleteIndex;
                cin >> athleteIndex;
            
                if (athleteIndex < 1 || athleteIndex > allAthletes.size()) {
                    cout << "Невірний вибір спортсмена.\n";
                    return {};
                }
            
                Athlete* athlete = allAthletes[athleteIndex - 1];
    vector<Coach*> result;
            
    const auto& coaches = athlete->getCoaches();

    for (auto it = coaches.begin(); it != coaches.end(); ++it) {
        Sport* sport = it->first;
        const vector<Coach*>& coachList = it->second;

        for (const auto& coach : coachList) {
            if (find(result.begin(), result.end(), coach) == result.end()) {
                result.push_back(coach);
            }
        }
    }
    if (result.empty()){

    }else{
        cout << "Список тренерів спортсмена " << athlete->getName() << ":\n";
    }
    return result;
 }


vector<Competition*> SportsQueries::getCompetitionsByDateAndOrganizer() { 
    cout << "Введіть початкову дату (YYYY-MM-DD): ";
                string startDate;
                cin >> startDate;
            
                cout << "Введіть кінцеву дату (YYYY-MM-DD): ";
                string endDate;
                cin >> endDate;
            
                cout << "Фільтрувати за організатором? (1 - так, 0 - ні): ";
                int filterByOrganizer;
                cin >> filterByOrganizer;
            
                string organizer;
                if (filterByOrganizer) {
                    
                    set<string> uniqueOrganizers;
                    for (const auto& competition : Competition::getAllCompetitions()) {
                        uniqueOrganizers.insert(competition->getOrganizer());
                    }
            
                    
                    cout << "Доступні організатори:\n";
                    vector<string> organizersList(uniqueOrganizers.begin(), uniqueOrganizers.end());
                    for (size_t i = 0; i < organizersList.size(); ++i) {
                        cout << i + 1 << " - " << organizersList[i] << endl;
                    }
            
                    cout << "Виберіть номер організатора: ";
                    int organizerIndex;
                    cin >> organizerIndex;
            
                    if (organizerIndex < 1 || organizerIndex > organizersList.size()) {
                        cout << "Невірний вибір організатора.\n";
                        return {};
                    }
            
                    organizer = organizersList[organizerIndex - 1];
                }
    vector<Competition*> result;

    for (const auto& competition : Competition::getAllCompetitions()) {
        if (competition->getDate() >= startDate && competition->getDate() <= endDate) {
            if (organizer.empty() || competition->getOrganizer() == organizer) {
                result.push_back(competition);
            }
        }
    }

    return result;
}


vector<Competition*> SportsQueries::getCompetitionsByFacilityAndSport() {
    cout << "Доступні спортивні споруди:\n";
                const auto& allFacilities = SportsFacility::getAllFacilities(); 
                for (size_t i = 0; i < allFacilities.size(); ++i) {
                    cout << i + 1 << " - ";
                    allFacilities[i]->displayInfo();
                    cout << endl;
                }
            
                cout << "Введіть номер спортивної споруди: ";
                int facilityIndex;
                cin >> facilityIndex;
            
                if (facilityIndex < 1 || facilityIndex > allFacilities.size()) {
                    cout << "Невірний вибір спортивної споруди.\n";
                    return {};
                }
            
                SportsFacility* facility = allFacilities[facilityIndex - 1];
            
                cout << "Фільтрувати за видом спорту? (1 - так, 0 - ні): ";
                int filterBySport;
                cin >> filterBySport;
            
                Sport* sport = nullptr;
                if (filterBySport) {
                    cout << "Доступні види спорту:\n";
                    const auto& allSports = Sport::getAllSports(); 
                    for (size_t i = 0; i < allSports.size(); ++i) {
                        cout << i + 1 << " - " << allSports[i]->getName() << endl;
                    }
            
                    cout << "Введіть номер виду спорту: ";
                    int sportIndex;
                    cin >> sportIndex;
            
                    if (sportIndex < 1 || sportIndex > allSports.size()) {
                        cout << "Невірний вибір виду спорту.\n";
                        return {};
                    }
                    sport = allSports[sportIndex - 1];
            
                    
                }
    vector<Competition*> result;

    for (const auto& competition : Competition::getAllCompetitions()) {
        if (competition->getFacility() == facility) {
            if (!sport || competition->getSport() == sport) {
                result.push_back(competition);
            }
        }
    }

    return result;
}

map<SportsClub*, int> SportsQueries::getClubsAndAthleteCounts() { 
    
    cout << "Введіть початкову дату (YYYY-MM-DD): ";
                string startDate;
                cin >> startDate;
            
                cout << "Введіть кінцеву дату (YYYY-MM-DD): ";
                string endDate;
                cin >> endDate;
    
    map<SportsClub*, set<Athlete*>> clubAthletesMap;

    for (const auto& participation : Participation::getAllParticipations()) {
        Competition* competition = participation->getCompetition();
        Athlete* athlete = participation->getAthlete();

        if (competition->getDate() >= startDate && competition->getDate() <= endDate) {
            SportsClub* club = athlete->getClub();
            if (club) {
                clubAthletesMap[club].insert(athlete);
            }
        }
    }

    map<SportsClub*, int> result;
    for (const auto& entry : clubAthletesMap) {
        result[entry.first] = entry.second.size();
    }

    return result;
}

vector<Coach*> SportsQueries::getCoachesBySport() { 
    
    cout << "Доступні види спорту:\n";
                const auto& allSports = Sport::getAllSports(); 
                for (size_t i = 0; i < allSports.size(); ++i) {
                    cout << i + 1 << " - " << allSports[i]->getName() << endl;
                }
            
                cout << "Введіть номер виду спорту: ";
                int sportIndex;
                cin >> sportIndex;
            
                if (sportIndex < 1 || sportIndex > allSports.size()) {
                    cout << "Невірний вибір виду спорту.\n";
                    return {};
                }
            
                Sport* sport = allSports[sportIndex - 1];
    vector<Coach*> result;

    for (const auto& coach : Coach::getAllCoaches()) {
        if (coach->getSport() == sport) {
            result.push_back(coach);
        }
    }
    cout << "Список тренерів для виду спорту \"" << sport->getName() << "\":\n";
    return result;
 }

vector<Athlete*> SportsQueries::getAthletesWithoutParticipation() { 

    cout << "Введіть початкову дату (YYYY-MM-DD): ";
                string startDate;
                cin >> startDate;
            
                cout << "Введіть кінцеву дату (YYYY-MM-DD): ";
                string endDate;
                cin >> endDate;
    vector<Athlete*> result;

    const auto& allAthletes = Athlete::getAllAthletes();

    for (const auto& athlete : allAthletes) {
        bool participated = false;

        for (const auto& participation : Participation::getAllParticipations()) {
            Competition* competition = participation->getCompetition();

            if (participation->getAthlete() == athlete &&
                competition->getDate() >= startDate &&
                competition->getDate() <= endDate) {
                participated = true;
                break;
            }
        }

        if (!participated) {
            result.push_back(athlete);
        }
    }
    cout << "Список спортсменів, які не брали участь у змаганнях у період з " << startDate << " по " << endDate << ":\n";
    return result;
}

map<string, int> SportsQueries::getOrganizersAndCompetitionCounts() { 

    cout << "Введіть початкову дату (YYYY-MM-DD): ";
                string startDate;
                cin >> startDate;
            
                cout << "Введіть кінцеву дату (YYYY-MM-DD): ";
                string endDate;
                cin >> endDate;
    map<string, int> organizerCounts;

    for (const auto& competition : Competition::getAllCompetitions()) {
        if (competition->getDate() >= startDate && competition->getDate() <= endDate) {
            organizerCounts[competition->getOrganizer()]++;
        }
    }

    return organizerCounts; }

map<SportsFacility*, vector<string>> SportsQueries::getFacilitiesAndCompetitionDates() { 
    cout << "Введіть початкову дату (YYYY-MM-DD): ";
                string startDate;
                cin >> startDate;
            
                cout << "Введіть кінцеву дату (YYYY-MM-DD): ";
                string endDate;
                cin >> endDate;
    map<SportsFacility*, vector<string>> facilityCompetitions;

    for (const auto& competition : Competition::getAllCompetitions()) {
        if (competition->getDate() >= startDate && competition->getDate() <= endDate) {
            SportsFacility* facility = competition->getFacility();
            if (facility) {
                facilityCompetitions[facility].push_back(competition->getDate());
            }
        }
    }

    return facilityCompetitions;
 }
