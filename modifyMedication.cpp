#include <iostream>

#include "modifyMedication.h"
#include "database.h"

using namespace std;

void modifyMedication()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    int patientId;

    cout << "Enter patient ID: ";
    cin >> patientId;

    string medicationName;

    cout << "Enter medication name: ";
    cin.ignore();
    getline(cin, medicationName);

    string dosage;

    cout << "Enter dosage: ";
    getline(cin, dosage);

    string frequency;

    cout << "Enter frequency: ";
    getline(cin, frequency);

    string notes;

    cout << "Enter notes (optional): ";
    getline(cin, notes);

    sqlite3_stmt* stmt;

    string sql = "INSERT INTO Prescriptions (patientId, medicationName, dosage, frequency, notes, updatedByUserId, updatedAt) VALUES (?, ?, ?, ?, ?, 0, datetime('now'))";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, patientId);
    sqlite3_bind_text(stmt, 2, medicationName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, dosage.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, frequency.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, notes.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cout << error << "Failed to save medication." << reset << endl;
    }
    else
    {
        cout << green << "Medication saved successfully." << reset << endl;
    }

    sqlite3_finalize(stmt);
    
    cout << "\nPress Enter to return...";
    cin.ignore();
    cin.get();
}