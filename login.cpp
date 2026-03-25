#include <iostream>
#include <string>

#include "login.h"
#include "database.h"
#include "patientMenu.h"
#include "nurseMenu.h"
#include "doctorMenu.h"
#include "pharmacistMenu.h"

using namespace std;

void login()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    int back = -1;

    string username;
    string password;

    cout << "=== Login ===" << endl << endl;

    cout << lightGreen << "Please enter your username: ";
    cin >> username;

    cout << lightGreen << "Please enter your password: ";
    cin >> password;

    sqlite3_stmt* stmt;
    string sql = "SELECT userId, passwordHash, role FROM Users WHERE username = ?";

    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (result != SQLITE_OK)
    {
        cout << error << "Database error." << reset << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        cout << "Loading profile.." << endl;
    }
    else
    {
        cout << error << "Username not found." << reset << endl;
        sqlite3_finalize(stmt);
        return;
    }

}