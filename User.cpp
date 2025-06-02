#include "User.h"
#include <iostream>
#include <fstream>

using namespace std;


bool loadAdminCredentials(string& adminLogin, string& adminPassword) {
    ifstream file("admin.txt");
    if (!file.is_open()) {
        cerr << "Помилка: Не вдалося відкрити файл admin.txt\n";
        return false;
    }

    getline(file, adminLogin);
    getline(file, adminPassword);
    file.close();
    return true;
}

User showLoginMenu() {
    User user;
    int choice;
    cout << "=== Система Входу ===\n";
    cout << "1. Гостьовий режим\n";
    cout << "2. Вхід як адміністратор\n";
    cout << "Оберіть опцію: ";
    cin >> choice;
    cin.ignore(); 

    if (choice == 1) {
        user.username = "Гість";
        user.accessLevel = 0;
    } else if (choice == 2) {
        string inputLogin, inputPassword;
        string correctLogin, correctPassword;
        if (!loadAdminCredentials(correctLogin, correctPassword)) {
            exit(1);
        }

        cout << "Введіть логін: ";
        getline(cin, inputLogin);
        cout << "Введіть пароль: ";
        getline(cin, inputPassword);

        if (inputLogin == correctLogin && inputPassword == correctPassword) {
            user.username = inputLogin;
            user.accessLevel = 1;
        } else {
            cout << "Невірний логін або пароль. Вхід як гість.\n";
            user.username = "Гість";
            user.accessLevel = 0;
        }
    } else {
        cout << "Невірний вибір. Вхід як гість.\n";
        user.username = "Гість";
        user.accessLevel = 0;
    }

    return user;
}
