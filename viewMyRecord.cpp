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
    //Gets the patient’s details using their userId
    string sql = "SELECT fullName, age, hasCancerHistory, isRecoveredFromCancer FROM Patients WHERE userId = ?";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int (stmt, 1, userId); //Binds the logged in userId to the ? placeholder

    if (sqlite3_step(stmt) == SQLITE_ROW) //Runs if the patient was found
    {
        //Gets the patients personal information
        string fullName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int age = sqlite3_column_int(stmt, 1);
        int hasCancerHistory = sqlite3_column_int(stmt, 2);
        int isRecoveredFromCancer = sqlite3_column_int(stmt, 3);

        cout << green << "Name: " <<fullName << endl;
        cout << green << "Age: " << age << endl;
        cout << green << "Cancer history: " << (hasCancerHistory ? "Yes" : "No") << reset << endl; //Displays bool as a yes or no
        cout << green << "Recovered from cancer: " << (isRecoveredFromCancer ? "Yes" : "No") << reset << endl;

        //Gets all conditions linked to patient
        sql = "SELECT conditionType FROM PatientConditions WHERE patientId = (SELECT patientId FROM Patients WHERE userId = ?)";

        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, userId);

        cout << green << "Conditions: " << reset << endl;
        
        while (sqlite3_step(stmt) == SQLITE_ROW) //Loops through each condition
        {
            string condition = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            cout << green << "- " << condition << reset << endl;
        }

        cout << endl << "Press Enter to return to menu...";
        cin.ignore();
        cin.get();

        sqlite3_finalize(stmt); //Releases prepared statement from memory
    }
    else
    {
        cout << "No record found." << endl;

        sqlite3_finalize(stmt);
    }
}