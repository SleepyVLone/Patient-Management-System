#include <iostream>

#include "viewPrescriptions.h"
#include "database.h"

using namespace std;

void viewPrescriptions()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    int patientId;

    cout << "Enter patient ID: ";
    cin >> patientId;

    sqlite3_stmt* stmt;

    string sql = "SELECT medicationName, dosage, frequency, notes, updatedAt FROM Prescriptions WHERE patientId = ?";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, patientId);

    bool found = false;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        found = true;

        string medicationName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string dosage = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string frequency = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string notes = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string updatedAt = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        cout << green << "Medication: " << medicationName << endl;
        cout << lightGreen << "Dosage: " << dosage << endl;
        cout << lightGreen << "Frequency: " << frequency << endl;
        cout << lightGreen << "Notes: " << notes << endl;
        cout << lightGreen << "Last updated: " << updatedAt << reset << endl;
        cout << "---" << endl;
    }

    if (!found)
    
    cout << error << "No prescriptions found." << reset << endl;

    sqlite3_finalize(stmt);
    
    cout << "\nPress Enter to return...";
    cin.ignore();
    cin.get();
}