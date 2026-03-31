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
    while (!(cin >> patientId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << error << "Invalid input. Please enter a number: " << reset;
    }

    sqlite3_stmt* stmt; //Used to prepare and run SQL queries

    string sql = "SELECT fullName, age, hasCancerHistory, isRecoveredFromCancer FROM Patients WHERE patientId = ?"; //Gets the patient details for the ID that was entered

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, patientId);

    if (sqlite3_step(stmt) == SQLITE_ROW) //Runs if statement below if patient is found
    {
        string fullName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); //Turns sqlite text into a C++ string

        int age = sqlite3_column_int(stmt, 1);
        int hasCancerHistory = sqlite3_column_int(stmt, 2);
        int isRecoveredFromCancer = sqlite3_column_int(stmt, 3);

        cout << green << "Name: " << fullName << endl;
        cout << "Age: " << age << endl;
        cout << "Cancer history: " << (hasCancerHistory ? "Yes" : "No") << endl;
        cout << "Recovered from cancer: " << (isRecoveredFromCancer ? "Yes" : "No") << reset << endl;

        //Gets all the conditions the patient has
        sql = "SELECT conditionType FROM PatientConditions WHERE patientId = ?";

        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, patientId);

        cout << green << "Conditions: " << reset << endl;

        while (sqlite3_step(stmt) == SQLITE_ROW) //Loops through all the conditions
        {
            string condition = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            cout << "- " << condition << endl;
        }
    }
    else
    {
        cout << error << "Patient not found." << reset << endl;
    }
    sqlite3_finalize(stmt); //releases the prepared statment from memory

    cout << "\nPress Enter to return...";
    cin.ignore();
    cin.get();
}