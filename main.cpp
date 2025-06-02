#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <Windows.h>
#include <set>
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
#include <fstream>
#include "SportsQueries.h"
#include "DataManager.h"
using namespace std;
using json = nlohmann::json;




int main() {
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);
    int choice;
    User currentUser = showLoginMenu();
   

    DataManager manager(&currentUser);
    manager.loadData("Date.json");
    do {
        manager.showMenu();
        cout << "Оберіть опцію: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                vector<SportsFacility*> filtered = SportsQueries::filterFacilities();

                
                if (filtered.empty()) {
                    cout << "Немає споруд, що відповідають критеріям.\n";
                } else {
                    cout << "Споруди, що відповідають критеріям:\n";
                    for (const auto& facility : filtered) {
                        facility->displayInfo();
                        cout << endl;
                    }
                }
                break;
            }
            case 2: {
                vector<Athlete*> athletes = SportsQueries::getAthletesBySportAndRank();
            
                
                if (athletes.empty()) {
                    cout << "Немає спортсменів, що відповідають критеріям.\n";
                } else {
                    cout << "Список спортсменів:\n";
                    for (const auto& athlete : athletes) {
                        athlete->displayInfo();
                        cout << endl;
                    }
                }
                break;
            }
            case 3: {
                
            
                
                vector<Athlete*> athletes = SportsQueries::getAthletesByCoachAndRank();
            
                
                if (athletes.empty()) {
                    cout << "Немає спортсменів, що відповідають критеріям.\n";
                } else {
                    cout << "Список спортсменів:\n";
                    for (const auto& athlete : athletes) {
                        athlete->displayInfo();
                        cout << endl;
                    }
                }
                break;
            }
            case 4: {
            
                
                vector<Athlete*> athletes = SportsQueries::getAthletesWithMultipleSports();
            
                cout << "Список спортсменів, що займаються більш ніж одним видом спорту:\n";
                if (athletes.empty()) {
                    cout << "Немає спортсменів, що займаються більш ніж одним видом спорту.\n";
                } else {
                    for (const auto& athlete : athletes) {
                        athlete->displayInfo();
                        cout << endl;
                    }
                }
                break;
            }
            case 5: {
            
                
                vector<Coach*> coaches = SportsQueries::getCoachesByAthlete();
            
                
                if (coaches.empty()) {
                    cout << "У спортсмена немає тренерів.\n";
                } else {
                    for (const auto& coach : coaches) {
                        cout << "- " << coach->getName() << " (Вид спорту: " << coach->getSport()->getName() << ")\n";
                    }
                }
                break;
            }
            case 6: {
                
                vector<Competition*> competitions = SportsQueries::getCompetitionsByDateAndOrganizer();
            
                
                if (competitions.empty()) {
                    cout << "Немає змагань, що відповідають критеріям.\n";
                } else {
                    cout << "Список змагань:\n";
                    for (const auto& competition : competitions) {
                        competition->displayInfo();
                        cout << endl;
                    }
                }
                break;
            }
            case 7: {
                cout << "Доступні змагання:\n";
                const auto& allCompetitions = Competition::getAllCompetitions(); 
                for (size_t i = 0; i < allCompetitions.size(); ++i) {
                    cout << i + 1 << " - " << allCompetitions[i]->getName() << " (" << allCompetitions[i]->getDate() << ")\n";
                }
            
                cout << "Введіть номер змагання: ";
                int competitionIndex;
                cin >> competitionIndex;
            
                if (competitionIndex < 1 || competitionIndex > allCompetitions.size()) {
                    cout << "Невірний вибір змагання.\n";
                    break;
                }
            
                Competition* selectedCompetition = allCompetitions[competitionIndex - 1];
            
                
                vector<Participation*> participations = Participation::getAllParticipations();
                vector<pair<Athlete*, int>> winners; 
            
                for (const auto& participation : participations) {
                    if (participation->getCompetition() == selectedCompetition) {
                        int place = participation->getPlace();
                        if (place >= 1 && place <= 3) { 
                            winners.emplace_back(participation->getAthlete(), place);
                        }
                    }
                }
            
                
                if (winners.empty()) {
                    cout << "Немає призерів для цього змагання.\n";
                } else {
                    cout << "Призери змагання \"" << selectedCompetition->getName() << "\":\n";
                    for (const auto& winner : winners) {
                        cout << "Місце: " << winner.second << endl;
                        winner.first->displayInfo();
                        cout << endl;
                    }
                }
                break;
            }
            case 8: {
                
            
                
                vector<Competition*> competitions = SportsQueries::getCompetitionsByFacilityAndSport();
            
                
                if (competitions.empty()) {
                    cout << "Немає змагань, що відповідають критеріям.\n";
                } else {
                    cout << "Список змагань:\n";
                    for (const auto& competition : competitions) {
                        competition->displayInfo();
                        cout << endl;
                    }
                }
                break;
            }
            case 9: {
                
                
                map<SportsClub*, int> clubsAndCounts = SportsQueries::getClubsAndAthleteCounts();
            
               
                if (clubsAndCounts.empty()) {
                    cout << "Немає клубів із спортсменами, які брали участь у змаганнях у заданий період.\n";
                } else {
                    cout << "Перелік клубів і кількість спортсменів:\n";
                    for (const auto& entry : clubsAndCounts) {
                        cout << "Клуб: " << entry.first->getName() << " - Кількість спортсменів: " << entry.second << endl;
                    }
                }
                break;
            }
            case 10: {
                vector<Coach*> coaches = SportsQueries::getCoachesBySport();
            
              
                if (coaches.empty()) {
                    cout << "Немає тренерів для цього виду спорту.\n";
                } else {
                    for (const auto& coach : coaches) {
                        coach->displayInfo();
                        cout << endl;
                    }
                }
                break;
            }
            case 11: {
            
                
                vector<Athlete*> athletes = SportsQueries::getAthletesWithoutParticipation();
            
                
                if (athletes.empty()) {
                    cout << "Усі спортсмени брали участь у змаганнях у заданий період.\n";
                } else {
                    for (const auto& athlete : athletes) {
                        athlete->displayInfo();
                        cout << endl;
                    }
                }
                break;
            }
            case 12: {
                
            
                
                map<string, int> organizers = SportsQueries::getOrganizersAndCompetitionCounts();
            
                
                if (organizers.empty()) {
                    cout << "Немає змагань, що відповідають критеріям.\n";
                } else {
                    cout << "Список організаторів і кількість проведених ними змагань:\n";
                    for (const auto& entry : organizers) {
                        cout << "Організатор: " << entry.first << " - Кількість змагань: " << entry.second << endl;
                    }
                }
                break;
            }
            case 13: {
                
            
                
                map<SportsFacility*, vector<string>> facilities = SportsQueries::getFacilitiesAndCompetitionDates();
            
               
                if (facilities.empty()) {
                    cout << "Немає змагань, що відповідають критеріям.\n";
                } else {
                    cout << "Перелік спортивних споруд та дати проведення змагань:\n";
                    for (const auto& entry : facilities) {
                        entry.first->displayInfo();
                        cout << "Дати проведення змагань:\n";
                        for (const auto& date : entry.second) {
                            cout << "  - " << date << endl;
                        }
                        cout << endl;
                    }
                }
                break;
            }
            case 14: {

                    cout << "1.Додати спортсмена\n";
                    cout << "2.Додати тренера\n";
                    cout << "3.Додати спортивну споруду\n";
                    cout << "4.Додати вид спорту\n";
                    cout << "5.Додати змагання\n";
                    cout << "6.Додати участь\n";
                    cout << "7.Додати клуб\n";
                    cout << "0. Вихід\n";

                    int addChoice;
                    cout << "Оберіть опцію: ";
                    cin >> addChoice;

                    switch (addChoice) {
                    case 1: {
                        manager.add_Athlete();
                        manager.loadData("Date.json");
                        break;
                    }
                    case 2: {
                        manager.add_Coach();
                        manager.loadData("Date.json");
                        break;
                    }
                    case 3: {
                        manager.add_SportsFacility();
                        manager.loadData("Date.json");
                        break;
                    }
                    case 4: {
                        manager.add_Sport();
                        manager.loadData("Date.json");
                        break;
                    }
                    case 5: {
                        manager.add_Competition();
                        manager.loadData("Date.json");
                        break;
                    }
                    case 6: {
                        manager.add_Participation();
                        manager.loadData("Date.json");
                        break;
                    }
                    case 7: {
                        manager.add_SportsClub();
                        manager.loadData("Date.json");
                        break;
                    }
                    case 0: {
                        cout << "Вихід з програми.\n";
                        break;
                    }
                    default: {
                        cout << "Невірний вибір, спробуйте ще раз.\n";
                        break;
                    }
                    }
                }
            case 0: {
                cout << "Вихід з програми.\n";
                break;
            }
            default: {
                cout << "Невірний вибір, спробуйте ще раз.\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}