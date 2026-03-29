#include <iostream>

#include "updatePatientInformation.h"
#include "database.h"

using namespace std;

void updatePatientInformation()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    int patientId;

    cout << "Enter patient ID: ";
    cin >> patientId;

    // Verify patient exists

    sqlite3_stmt* checkStmt;

    string checkSql = "SELECT patientId FROM Patients WHERE patientId = ?";

    sqlite3_prepare_v2(db, checkSql.c_str(), -1, &checkStmt, nullptr);
    sqlite3_bind_int(checkStmt, 1, patientId);

    if (sqlite3_step(checkStmt) != SQLITE_ROW)
    {
        cout << error << "Patient not found." << reset << endl;
        sqlite3_finalize(checkStmt);
        cout << "\nPress Enter to return...";
        cin.ignore();
        cin.get();
        return;
    }
    sqlite3_finalize(checkStmt);

    string fullName;
    int age;

    cout << "Enter new full name: ";
    cin.ignore();
    getline(cin, fullName);

    cout << "Enter new age: ";
    cin >> age;

    sqlite3_stmt* stmt;

    string sql = "UPDATE Patients SET fullName = ?, age = ? WHERE patientId = ?";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, fullName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, age);
    sqlite3_bind_int(stmt, 3, patientId);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cout << error << "Failed to update patient." << reset << endl;
    }
    else
    {
        cout << green << "Patient updated successfully." << reset << endl << endl;
    }
    sqlite3_finalize(stmt);

    cout << "Press Enter to return...";
    cin.ignore();
    cin.get();
}