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
    while (!(cin >> patientId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << error << "Invalid input. Please enter a number: " << reset;
    }

    // Verify patient exists before attempting to update

    sqlite3_stmt* checkStmt;

    string checkSql = "SELECT patientId FROM Patients WHERE patientId = ?";

    sqlite3_prepare_v2(db, checkSql.c_str(), -1, &checkStmt, nullptr);
    sqlite3_bind_int(checkStmt, 1, patientId);

    if (sqlite3_step(checkStmt) != SQLITE_ROW) //if statement below runs if no patient is found
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
    if (fullName.empty())
    {
        cout << error << "Full name cannot be empty." << reset << endl;

        return;
    }

    cout << "Enter new age: ";
    while (!(cin >> age) || age <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << error << "Invalid age. Please enter a positive number: " << reset;
    }

    sqlite3_stmt* stmt;

    string sql = "UPDATE Patients SET fullName = ?, age = ? WHERE patientId = ?"; //Modifies the patient record matching the patientId

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