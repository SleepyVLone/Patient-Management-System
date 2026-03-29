#include <iostream>

#include "viewPatientDetails.h"
#include "database.h"

using namespace std;

void viewPatientDetails()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    int patientId;

    cout << "Enter patient ID: ";
    cin >> patientId;

    sqlite3_stmt* stmt;

    string sql = "SELECT fullName, age, hasCancerHistory, isRecoveredFromCancer FROM Patients WHERE patientId = ?";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, patientId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        string fullName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        int age = sqlite3_column_int(stmt, 1);
        int hasCancerHistory = sqlite3_column_int(stmt, 2);
        int isRecoveredFromCancer = sqlite3_column_int(stmt, 3);

        cout << green << "Name: " << fullName << endl;
        cout << "Age: " << age << endl;
        cout << "Cancer history: " << (hasCancerHistory ? "Yes" : "No") << endl;
        cout << "Recovered from cancer: " << (isRecoveredFromCancer ? "Yes" : "No") << reset << endl;

        sql = "SELECT conditionType FROM PatientConditions WHERE patientId = ?";

        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, patientId);

        cout << green << "Conditions: " << reset << endl;

        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            string condition = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            cout << "- " << condition << endl;
        }
    }
    else
    {
        cout << error << "Patient not found." << reset << endl;
    }
    sqlite3_finalize(stmt);

    cout << "\nPress Enter to return...";
    cin.ignore();
    cin.get();
}