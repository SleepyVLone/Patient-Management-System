#include <iostream>

#include "viewMyRecord.h"
#include "database.h"

using namespace std;

void viewMyRecord(int userId)
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    sqlite3_stmt* stmt;

    string sql = "SELECT fullName, age, hasCancerHistory, isRecoveredFromCancer FROM Patients WHERE userId = ?";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int (stmt, 1, userId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        string fullName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int age = sqlite3_column_int(stmt, 1);
        int hasCancerHistory = sqlite3_column_int(stmt, 2);
        int isRecoveredFromCancer = sqlite3_column_int(stmt, 3);

        cout << green << "Name: " <<fullName << endl;
        cout << green << "Age: " << age << endl;
        cout << green << "Cancer history: " << (hasCancerHistory ? "Yes" : "No") << reset << endl;
        cout << green << "Recovered from cancer: " << (isRecoveredFromCancer ? "Yes" : "No") << reset << endl;

        cout << endl << "Press Enter to return to menu...";
        cin.ignore();
        cin.get();

        sqlite3_finalize(stmt);
    }
    else
    {
        cout << "No record found." << endl;

        sqlite3_finalize(stmt);
    }
}