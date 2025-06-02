#include "DataManager.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Athlete.h"
#include "Coach.h"
#include "Competition.h"
#include "Participation.h"
#include "SportFacility.h"
#include "Sport.h"
#include "Stadium.h"
#include "Court.h"
#include "SportHall.h"
#include "SwimmingPool.h"
#include "Gym.h"
#include "SportsClub.h"
#include "json.hpp"
#include "User.h" 
using json = nlohmann::json;
using namespace std;


DataManager::DataManager(User* user) : user(user) {}

void DataManager::saveData(const std::string& filename) {
    if (user->getAccessLevel() != 1) {
        std::cerr << "Доступ заборонено: недостатній рівень доступу\n";
        return;
    }

    json data;

    for (const auto& club : SportsClub::getAllSportsClubs()) {
        json clubData = {
            {"ID", club->getId()},
            {"Name", club->getName()},
            {"ContactInfo", club->getContactInfo()} 
        };
        data["SportsClub"].push_back(clubData);
    }

    for (const auto& sport : Sport::getAllSports()) {
        json sportData = {
            {"ID", sport->getId()},
            {"Name", sport->getName()}
        };
        data["Sport"].push_back(sportData);
    }

    for (const auto& coach : Coach::getAllCoaches()) {
        json coachData = {
            {"ID", coach->getId()},
            {"Name", coach->getName()},
            {"Sport", coach->getSport()->getId()}
        };
        data["Coach"].push_back(coachData);
    }

    for (const auto& athlete : Athlete::getAllAthletes()) {
        json athleteData = {
            {"ID", athlete->getId()},
            {"Name", athlete->getName()},
            {"Club", athlete->getClub()->getId()}
        };

        for (const auto& sportRankPair : athlete->getSports()) {
            Sport* sport = sportRankPair.first;
            int rank = sportRankPair.second;
            athleteData["Sports"].push_back({
                {"ID", sport->getId()},
                {"Rank", rank}
            });
        }

        for (const auto& sportCoachesPair : athlete->getCoaches()) {
            Sport* sport = sportCoachesPair.first;
            const auto& coaches = sportCoachesPair.second;
            for (const auto& coach : coaches) {
                athleteData["Coaches"].push_back(coach->getId());
            }
        }

        data["Athlete"].push_back(athleteData);
    }

    for (const auto& competition : Competition::getAllCompetitions()) {
        json competitionData = {
            {"ID", competition->getId()},
            {"Name", competition->getName()},
            {"Date", competition->getDate()},
            {"Organizer", competition->getOrganizer()},
            {"Facility", competition->getFacility()->getId()},
            {"Sport", competition->getSport()->getId()}
        };
        data["Competition"].push_back(competitionData);
    }

    for (const auto& participation : Participation::getAllParticipations()) {
        json participationData = {
            {"Athlete", participation->getAthlete()->getId()},
            {"Competition", participation->getCompetition()->getId()},
            {"Place", participation->getPlace()}
        };
        data["Participation"].push_back(participationData);
    }


    for (const auto& facility : SportsFacility::getAllFacilities()) {
        json facilityData = {
            {"ID", facility->getId()},
            {"Name", facility->getName()},
            {"Address", facility->getAddress()}
        };

        if (dynamic_cast<Stadium*>(facility)) {
            Stadium* stadium = dynamic_cast<Stadium*>(facility);
            facilityData["Type"] = "Stadium";
            facilityData["Capacity"] = stadium->getCapacity();
        } else if (dynamic_cast<Court*>(facility)) {
            Court* court = dynamic_cast<Court*>(facility);
            facilityData["Type"] = "Court";
            facilityData["SurfaceType"] = court->getSurfaceType();
        } else if (dynamic_cast<SportHall*>(facility)) {
            SportHall* sportHall = dynamic_cast<SportHall*>(facility);
            facilityData["Type"] = "sporthall";
            facilityData["Area"] = sportHall->getArea();
        } else if (dynamic_cast<SwimmingPool*>(facility)) {
            SwimmingPool* swimmingPool = dynamic_cast<SwimmingPool*>(facility);
            facilityData["Type"] = "swimmingpool";
            facilityData["Length"] = swimmingPool->getLength();
        } 

        data["SportsFacility"].push_back(facilityData);
    }


    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису: " << filename << std::endl;
        return;
    }
    file << data.dump(4); 
    file.close();
}

void DataManager::loadData(const std::string& filename) {
    if (user->getAccessLevel() != 1) {
        std::cerr << "Доступ заборонено: недостатній рівень доступу\n";
        return;
    }

    Sport::allSports.clear();
    SportsFacility::allFacilities.clear();
    Coach::allCoaches.clear();
    Athlete::allAthletes.clear();
    Competition::allCompetitions.clear();
    Participation::allParticipations.clear();
    SportsClub::allSportsClubs.clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл " << filename << std::endl;
        return;
    }

    json data;
    file >> data;

    if (data.contains("SportsClub")) {
        for (const auto& club : data["SportsClub"]) {
            int id = club["ID"];
            string name = club["Name"];
            string contactInfo = club["ContactInfo"];
            new SportsClub(id, name, contactInfo);
        }
        
        
        
    }

    if (data.contains("Sport")) {
        for (const auto& sport : data["Sport"]) {
            int id = sport["ID"];
            std::string name = sport["Name"];
            new Sport(id, name);
        }
    }
    
    if (data.contains("SportsFacility")) {
        for (const auto& facility : data["SportsFacility"]) {
            int id = facility["ID"];
            std::string name = facility["Name"];
            std::string address = facility["Address"];
            std::string type = facility["Type"];

            if (type == "Stadium") {
                int capacity = facility["Capacity"];
                new Stadium(id, name, address, capacity);
            } else if (type == "Court") {
                std::string surface = facility["SurfaceType"];
                new Court(id, name, address, surface);
            } else if (type == "sporthall") {
                float area = facility["Area"];
                new SportHall(id, name, address, area);
            } else if (type == "swimmingpool") {
                float length = facility["Length"];
                new SwimmingPool(id, name, address, length);
            } else {
                new SportsFacility(id, name, address);
            }
        }
    }

    if (data.contains("Coach")) {
        for (const auto& coach : data["Coach"]) {
            int id = coach["ID"];
            std::string name = coach["Name"];
            int sportID = coach["Sport"];

            Sport* sportPtr = Sport::findById(sportID);
            if (sportPtr) {
                new Coach(id, name, sportPtr);
            }
        }
    }

    if (data.contains("Athlete")) {
        for (const auto& athlete : data["Athlete"]) {
            int id = athlete["ID"];
            std::string name = athlete["Name"];
            int clubID = athlete["Club"];
            SportsClub* clubPtr = SportsClub::findById(clubID); 
            Athlete* newAthlete = new Athlete(id, name, clubPtr);

            for (const auto& sportData : athlete["Sports"]) {
                int sportID = sportData["ID"];
                int rank = sportData["Rank"];
                Sport* sportPtr = Sport::findById(sportID);
                if (sportPtr) {
                    newAthlete->addSport(sportPtr, rank);
                }
            }

            for (int coachID : athlete["Coaches"]) {
                Coach* coachPtr = Coach::findById(coachID);
                if (coachPtr) {
                    newAthlete->addCoach(coachPtr->getSport(), coachPtr);
                }
            }

            newAthlete;
        }
    }

    if (data.contains("Competition")) {
        for (const auto& competition : data["Competition"]) {
            int id = competition["ID"];
            std::string name = competition["Name"];
            std::string date = competition["Date"];
            std::string organizer = competition["Organizer"];
            int facilityID = competition["Facility"];
            int sportID = competition["Sport"];

            SportsFacility* facilityPtr = SportsFacility::findById(facilityID);
            Sport* sportPtr = Sport::findById(sportID);

            if (facilityPtr && sportPtr) {
                new Competition(id, name, date, organizer, facilityPtr, sportPtr);
            }
        }
    }

    if (data.contains("Participation")) {
        for (const auto& participation : data["Participation"]) {
            int athleteID = participation["Athlete"];
            int competitionID = participation["Competition"];
            int place = participation["Place"];

            Athlete* athletePtr = Athlete::findById(athleteID);
            Competition* competitionPtr = Competition::findById(competitionID);

            if (athletePtr && competitionPtr) {
                new Participation(athletePtr, competitionPtr, place);
            }
        }
    }
}

void DataManager::add_Athlete() {
    if (user->getAccessLevel() != 1) {
        std::cerr << "Доступ заборонено: недостатній рівень доступу\n";
        return;
    }

    cout << "Додати нового атлета:\n";
            
                int athleteId = Athlete::getAllAthletes().empty() ? 1 : Athlete::getAllAthletes().back()->getId() + 1;
            
                cout << "Введіть ім'я атлета: ";
                string athleteName;
                cin.ignore(); 
                getline(cin, athleteName);
            
                
                cout << "Доступні спортивні клуби:\n";
                const auto& allClubs = SportsClub::getAllSportsClubs();
                for (size_t i = 0; i < allClubs.size(); ++i) {
                    cout << i + 1 << " - " << allClubs[i]->getName() << endl;
                }
                cout << "Введіть номер клубу (0 для створення нового): ";
                int clubIndex;
                cin >> clubIndex;
            
                SportsClub* selectedClub = nullptr;
                if (clubIndex == 0) {
                    
                    int clubId = SportsClub::getAllSportsClubs().empty() ? 1 : SportsClub::getAllSportsClubs().back()->getId() + 1;
            
                    cout << "Введіть назву клубу: ";
                    string clubName;
                    cin.ignore();
                    getline(cin, clubName);
            
                    cout << "Введіть контактну інформацію клубу: ";
                    string contactInfo;
                    getline(cin, contactInfo);
            
                    selectedClub = new SportsClub(clubId, clubName, contactInfo);
                    saveData("Date.json"); 
                } else if (clubIndex > 0 && clubIndex <= allClubs.size()) {
                    selectedClub = allClubs[clubIndex - 1];
                } else {
                    cout << "Невірний вибір клубу.\n";
                    return;
                }
            
                
                Athlete* newAthlete = new Athlete(athleteId, athleteName, selectedClub);
            
                
                cout << "Додати види спорту для атлета:\n";
                vector<Sport*> selectedSports;
                while (true) {
                    cout << "Доступні види спорту:\n";
                    const auto& allSports = Sport::getAllSports();
                    for (size_t i = 0; i < allSports.size(); ++i) {
                        cout << i + 1 << " - " << allSports[i]->getName() << endl;
                    }
                    cout << "Введіть номер виду спорту (0 для створення нового, -1 для завершення): ";
                    int sportIndex;
                    cin >> sportIndex;
            
                    if (sportIndex == -1) {
                        break;
                    }
            
                    Sport* selectedSport = nullptr;
                    if (sportIndex == 0) {
                        
                        int sportId = Sport::getAllSports().empty() ? 1 : Sport::getAllSports().back()->getId() + 1;
            
                        cout << "Введіть назву виду спорту: ";
                        string sportName;
                        cin.ignore();
                        getline(cin, sportName);
            
                        selectedSport = new Sport(sportId, sportName);
                        saveData("Date.json"); 
                    } else if (sportIndex > 0 && sportIndex <= allSports.size()) {
                        selectedSport = allSports[sportIndex - 1];
                    } else {
                        cout << "Невірний вибір виду спорту.\n";
                        continue;
                    }
            
                    cout << "Введіть розряд для цього виду спорту: ";
                    int rank;
                    cin >> rank;
            
                    newAthlete->addSport(selectedSport, rank);
                    selectedSports.push_back(selectedSport);
                }
            
                
                cout << "Додати тренерів для атлета:\n";
                while (true) {
                    cout << "Доступні тренери для вибраних видів спорту:\n";
                    const auto& allCoaches = Coach::getAllCoaches();
                    vector<Coach*> filteredCoaches;
                    for (const auto& coach : allCoaches) {
                        if (find(selectedSports.begin(), selectedSports.end(), coach->getSport()) != selectedSports.end()) {
                            filteredCoaches.push_back(coach);
                        }
                    }
            
                    for (size_t i = 0; i < filteredCoaches.size(); ++i) {
                        cout << i + 1 << " - " << filteredCoaches[i]->getName() << " (" << filteredCoaches[i]->getSport()->getName() << ")\n";
                    }
                    cout << "Введіть номер тренера (0 для створення нового, -1 для завершення): ";
                    int coachIndex;
                    cin >> coachIndex;
            
                    if (coachIndex == -1) {
                        break;
                    }
            
                    Coach* selectedCoach = nullptr;
                    if (coachIndex == 0) {
                        
                        int coachId = Coach::getAllCoaches().empty() ? 1 : Coach::getAllCoaches().back()->getId() + 1;
            
                        cout << "Введіть ім'я тренера: ";
                        string coachName;
                        cin.ignore();
                        getline(cin, coachName);
            
                        cout << "Доступні види спорту:\n";
                        for (size_t i = 0; i < selectedSports.size(); ++i) {
                            cout << i + 1 << " - " << selectedSports[i]->getName() << endl;
                        }
                        cout << "Введіть номер виду спорту для тренера: ";
                        int sportIndex;
                        cin >> sportIndex;
            
                        Sport* coachSport = nullptr;
                        if (sportIndex > 0 && sportIndex <= selectedSports.size()) {
                            coachSport = selectedSports[sportIndex - 1];
                        } else {
                            cout << "Невірний вибір виду спорту.\n";
                            continue;
                        }
            
                        selectedCoach = new Coach(coachId, coachName, coachSport);
                        saveData("Date.json"); 
                    } else if (coachIndex > 0 && coachIndex <= filteredCoaches.size()) {
                        selectedCoach = filteredCoaches[coachIndex - 1];
                    } else {
                        cout << "Невірний вибір тренера.\n";
                        continue;
                    }
            
                    newAthlete->addCoach(selectedCoach->getSport(), selectedCoach);
                }
            
                saveData("Date.json"); 
                cout << "Новий атлет успішно доданий!\n";
                return;
}

void DataManager::add_Sport() {
    if (user->getAccessLevel() != 1) {
        std::cerr << "Доступ заборонено: недостатній рівень доступу\n";
        return;
    }

    cout << "Додати новий вид спорту:\n";

    
    int sportId = Sport::getAllSports().empty() ? 1 : Sport::getAllSports().back()->getId() + 1;

    cout << "Введіть назву виду спорту: ";
    string sportName;
    cin.ignore();
    getline(cin, sportName);

    
    Sport* newSport = new Sport(sportId, sportName);

    
    saveData("Date.json");

    cout << "Новий вид спорту успішно доданий!\n";
}

void DataManager::add_Coach() {
    if (user->getAccessLevel() != 1) {
        std::cerr << "Доступ заборонено: недостатній рівень доступу\n";
        return;
    }

    cout << "Додати нового тренера:\n";

    
    int coachId = Coach::getAllCoaches().empty() ? 1 : Coach::getAllCoaches().back()->getId() + 1;

    cout << "Введіть ім'я тренера: ";
    string coachName;
    cin.ignore(); 
    getline(cin, coachName);

    
    cout << "Доступні види спорту:\n";
    const auto& allSports = Sport::getAllSports();
    for (size_t i = 0; i < allSports.size(); ++i) {
        cout << i + 1 << " - " << allSports[i]->getName() << endl;
    }
    cout << "Введіть номер виду спорту (0 для створення нового): ";
    int sportIndex;
    cin >> sportIndex;

    Sport* selectedSport = nullptr;
    if (sportIndex == 0) {
        
        int sportId = Sport::getAllSports().empty() ? 1 : Sport::getAllSports().back()->getId() + 1;

        cout << "Введіть назву виду спорту: ";
        string sportName;
        cin.ignore();
        getline(cin, sportName);

        selectedSport = new Sport(sportId, sportName);
        saveData("Date.json"); 
    } else if (sportIndex > 0 && sportIndex <= allSports.size()) {
        selectedSport = allSports[sportIndex - 1];
    } else {
        cout << "Невірний вибір виду спорту.\n";
        return;
    }

   
    Coach* newCoach = new Coach(coachId, coachName, selectedSport);

    
    saveData("Date.json");

    cout << "Новий тренер успішно доданий!\n";
}

void DataManager::add_SportsClub() {
    if (user->getAccessLevel() != 1) {
        std::cerr << "Доступ заборонено: недостатній рівень доступу\n";
        return;
    }
    cout << "Додати новий спортивний клуб:\n";

    
    int clubId = SportsClub::getAllSportsClubs().empty() ? 1 : SportsClub::getAllSportsClubs().back()->getId() + 1;

    cout << "Введіть назву спортивного клубу: ";
    string clubName;
    cin.ignore(); 
    getline(cin, clubName);

    cout << "Введіть контактну інформацію клубу: ";
    string contactInfo;
    getline(cin, contactInfo);

    
    SportsClub* newClub = new SportsClub(clubId, clubName, contactInfo);

    
    saveData("Date.json");

    cout << "Новий спортивний клуб успішно доданий!\n";
}

void DataManager::add_Competition() {
    if (user->getAccessLevel() != 1) {
        std::cerr << "Доступ заборонено: недостатній рівень доступу\n";
        return;
    }

    cout << "Додати нове змагання:\n";

    
    int competitionId = Competition::getAllCompetitions().empty() ? 1 : Competition::getAllCompetitions().back()->getId() + 1;

    cout << "Введіть назву змагання: ";
    string competitionName;
    cin.ignore(); 
    getline(cin, competitionName);

    cout << "Введіть дату змагання (YYYY-MM-DD): ";
    string competitionDate;
    cin >> competitionDate;

    cout << "Введіть організатора змагання: ";
    string organizer;
    cin.ignore();
    getline(cin, organizer);

   
    cout << "Доступні спортивні споруди:\n";
    const auto& allFacilities = SportsFacility::getAllFacilities();
    for (size_t i = 0; i < allFacilities.size(); ++i) {
        cout << i + 1 << " - ";
        allFacilities[i]->displayInfo();
        cout << endl;
    }
    cout << "Введіть номер спортивної споруди (0 для створення нової): ";
    int facilityIndex;
    cin >> facilityIndex;

    SportsFacility* selectedFacility = nullptr;
    if (facilityIndex == 0) {
        
        int facilityId = SportsFacility::getAllFacilities().empty() ? 1 : SportsFacility::getAllFacilities().back()->getId() + 1;

        cout << "Введіть назву спортивної споруди: ";
        string facilityName;
        cin.ignore();
        getline(cin, facilityName);

        cout << "Введіть адресу спортивної споруди: ";
        string facilityAddress;
        getline(cin, facilityAddress);

        cout << "Оберіть тип споруди (1 - Стадіон, 2 - Корт, 3 - Спортзал, 4 - Басейн, 5 - Тренажерний зал): ";
        int facilityType;
        cin >> facilityType;

        switch (facilityType) {
            case 1: {
                cout << "Введіть місткість стадіону: ";
                int capacity;
                cin >> capacity;
                selectedFacility = new Stadium(facilityId, facilityName, facilityAddress, capacity);
                break;
            }
            case 2: {
                cout << "Введіть тип покриття корту: ";
                string surfaceType;
                cin.ignore();
                getline(cin, surfaceType);
                selectedFacility = new Court(facilityId, facilityName, facilityAddress, surfaceType);
                break;
            }
            case 3: {
                cout << "Введіть площу спортзалу: ";
                float area;
                cin >> area;
                selectedFacility = new SportHall(facilityId, facilityName, facilityAddress, area);
                break;
            }
            case 4: {
                cout << "Введіть довжину басейну: ";
                float length;
                cin >> length;
                selectedFacility = new SwimmingPool(facilityId, facilityName, facilityAddress, length);
                break;
            }
            case 5: {
                cout << "Введіть кількість тренажерів у залі: ";
                int numMachines;
                cin >> numMachines;
                selectedFacility = new Gym(facilityId, facilityName, facilityAddress, numMachines);
                break;
            }
            default:
                cout << "Невірний вибір типу споруди.\n";
                return;
        }
    } else if (facilityIndex > 0 && facilityIndex <= allFacilities.size()) {
        selectedFacility = allFacilities[facilityIndex - 1];
    } else {
        cout << "Невірний вибір спортивної споруди.\n";
        return;
    }

    // Вибір або створення виду спорту
    cout << "Доступні види спорту:\n";
    const auto& allSports = Sport::getAllSports();
    for (size_t i = 0; i < allSports.size(); ++i) {
        cout << i + 1 << " - " << allSports[i]->getName() << endl;
    }
    cout << "Введіть номер виду спорту (0 для створення нового): ";
    int sportIndex;
    cin >> sportIndex;

    Sport* selectedSport = nullptr;
    if (sportIndex == 0) {
        // Генерація нового ID для виду спорту
        int sportId = Sport::getAllSports().empty() ? 1 : Sport::getAllSports().back()->getId() + 1;

        cout << "Введіть назву виду спорту: ";
        string sportName;
        cin.ignore();
        getline(cin, sportName);

        selectedSport = new Sport(sportId, sportName);
    } else if (sportIndex > 0 && sportIndex <= allSports.size()) {
        selectedSport = allSports[sportIndex - 1];
    } else {
        cout << "Невірний вибір виду спорту.\n";
        return;
    }

    // Створення нового змагання
    Competition* newCompetition = new Competition(competitionId, competitionName, competitionDate, organizer, selectedFacility, selectedSport);

    // Збереження даних у JSON
    saveData("Date.json");

    cout << "Нове змагання успішно додано!\n";
}

void DataManager::add_SportsFacility() {
    if (user->getAccessLevel() != 1) {
        std::cerr << "Доступ заборонено: недостатній рівень доступу\n";
        return;
    }
    cout << "Додати нове спортивне місце:\n";

    
    int facilityId = SportsFacility::getAllFacilities().empty() ? 1 : SportsFacility::getAllFacilities().back()->getId() + 1;

    cout << "Введіть назву спортивного місця: ";
    string facilityName;
    cin.ignore(); 
    getline(cin, facilityName);

    cout << "Введіть адресу спортивного місця: ";
    string facilityAddress;
    getline(cin, facilityAddress);

    cout << "Оберіть тип спортивного місця (1 - Стадіон, 2 - Корт, 3 - Спортзал, 4 - Басейн, 5 - Тренажерний зал): ";
    int facilityType;
    cin >> facilityType;

    SportsFacility* newFacility = nullptr;

    switch (facilityType) {
        case 1: {
            cout << "Введіть місткість стадіону: ";
            int capacity;
            cin >> capacity;
            newFacility = new Stadium(facilityId, facilityName, facilityAddress, capacity);
            break;
        }
        case 2: {
            cout << "Введіть тип покриття корту: ";
            string surfaceType;
            cin.ignore();
            getline(cin, surfaceType);
            newFacility = new Court(facilityId, facilityName, facilityAddress, surfaceType);
            break;
        }
        case 3: {
            cout << "Введіть площу спортзалу: ";
            float area;
            cin >> area;
            newFacility = new SportHall(facilityId, facilityName, facilityAddress, area);
            break;
        }
        case 4: {
            cout << "Введіть довжину басейну: ";
            float length;
            cin >> length;
            newFacility = new SwimmingPool(facilityId, facilityName, facilityAddress, length);
            break;
        }
        case 5: {
            cout << "Введіть кількість тренажерів у залі: ";
            int numMachines;
            cin >> numMachines;
            newFacility = new Gym(facilityId, facilityName, facilityAddress, numMachines);
            break;
        }
        default:
            cout << "Невірний вибір типу спортивного місця.\n";
            return;
    }

    
    saveData("Date.json");

    cout << "Нове спортивне місце успішно додано!\n";
}

void DataManager::add_Participation() {
    if (user->getAccessLevel() != 1) {
        std::cerr << "Доступ заборонено: недостатній рівень доступу\n";
        return;
    }

    cout << "Додати нову участь:\n";

    
    cout << "Доступні атлети:\n";
    const auto& allAthletes = Athlete::getAllAthletes();
    for (size_t i = 0; i < allAthletes.size(); ++i) {
        cout << i + 1 << " - " << allAthletes[i]->getName() << endl;
    }
    cout << "Введіть номер атлета: ";
    int athleteIndex;
    cin >> athleteIndex;

    Athlete* selectedAthlete = nullptr;
    if (athleteIndex > 0 && athleteIndex <= allAthletes.size()) {
        selectedAthlete = allAthletes[athleteIndex - 1];
    } else {
        cout << "Невірний вибір атлета.\n";
        return;
    }

    
    cout << "Доступні змагання:\n";
    const auto& allCompetitions = Competition::getAllCompetitions();
    for (size_t i = 0; i < allCompetitions.size(); ++i) {
        cout << i + 1 << " - " << allCompetitions[i]->getName() << " (" << allCompetitions[i]->getDate() << ")" << endl;
    }
    cout << "Введіть номер змагання: ";
    int competitionIndex;
    cin >> competitionIndex;

    Competition* selectedCompetition = nullptr;
    if (competitionIndex > 0 && competitionIndex <= allCompetitions.size()) {
        selectedCompetition = allCompetitions[competitionIndex - 1];
    } else {
        cout << "Невірний вибір змагання.\n";
        return;
    }

    
    cout << "Введіть місце (1 - 3): ";
    int place;
    cin >> place;

    if (place < 1 || place > 3) {
        cout << "Невірне місце. Місце повинно бути від 1 до 3.\n";
        return;
    }

    
    Participation* newParticipation = new Participation(selectedAthlete, selectedCompetition, place);

    
    saveData("Date.json");

    cout << "Нова участь успішно додана!\n";
}

void DataManager::showMenu() {
    int accessLevel = user->getAccessLevel();
    if(accessLevel){
        cout << "\nМеню:\n";
        
        cout << "1. Отримати перелік спортивних споруд\n";
        cout << "2. Отримати список спортсменів за видом спорту\n";
        cout << "3. Отримати список спортсменів, що тренуються у тренера\n";
        cout << "4. Отримати список спортсменів з більш ніж одним видом спорту\n";
        cout << "5. Отримати список тренерів зазначеного спортсмена\n";
        cout << "6. Отримати перелік змагань за період часу\n";
        cout << "7. Отримати список призерів змагання\n";
        cout << "8. Отримати перелік змагань за спортивною спорудою\n";
        cout << "9. Отримати перелік клубів і число спортсменів, що брали участь у змаганнях\n";
        cout << "10. Отримати список тренерів за видом спорту\n";
        cout << "11. Отримати список спортсменів, що не брали участь у змаганнях\n";
        cout << "12. Отримати список організаторів і число проведених змагань\n";
        cout << "13. Отримати перелік споруд та дати проведення на них змагань\n";
        cout << "14. Додати дані\n";
        cout << "0. Вийти\n";

        }
        else{
            cout << "\nМеню:\n";
        cout << "1. Отримати перелік спортивних споруд\n";
        cout << "2. Отримати список спортсменів за видом спорту\n";
        cout << "3. Отримати список спортсменів, що тренуються у тренера\n";
        cout << "4. Отримати список спортсменів з більш ніж одним видом спорту\n";
        cout << "5. Отримати список тренерів зазначеного спортсмена\n";
        cout << "6. Отримати перелік змагань за період часу\n";
        cout << "7. Отримати список призерів змагання\n";
        cout << "8. Отримати перелік змагань за спортивною спорудою\n";
        cout << "9. Отримати перелік клубів і число спортсменів, що брали участь у змаганнях\n";
        cout << "10. Отримати список тренерів за видом спорту\n";
        cout << "11. Отримати список спортсменів, що не брали участь у змаганнях\n";
        cout << "12. Отримати список організаторів і число проведених змагань\n";
        cout << "13. Отримати перелік споруд та дати проведення на них змагань\n";
        cout << "0. Вийти\n";
        }
}
