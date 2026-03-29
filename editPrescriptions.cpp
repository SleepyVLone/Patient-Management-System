#include <iostream>

#include "editPrescriptions.h"
#include "database.h"

using namespace std;

void editPrescriptions()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    int patientId;

    cout << "Enter patient ID: ";
    cin >> patientId;

    // Show the existing prescriptions first

    sqlite3_stmt* stmt;

    string sql = "SELECT prescriptionId, medicationName, dosage, frequency FROM Prescriptions WHERE patientId = ?";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, patientId);

    bool found = false;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        found = true;

        int prescriptionId = sqlite3_column_int(stmt, 0);
        string medicationName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string dosage = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string frequency = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        cout << green << "ID: " << prescriptionId << " | " << medicationName << " | " << dosage << " | " << frequency << reset << endl;
    }
    sqlite3_finalize(stmt);

    if (!found)
    {
        cout << error << "No prescriptions found." << reset << endl << endl;
        cout << "Press Enter to return...";
        cin.ignore();
        cin.get();

        return;
    }

    int prescriptionId;

    cout << "Enter prescription ID to edit: ";
    cin >> prescriptionId;

    string medicationName;
    string dosage;
    string frequency;
    string notes;

    cout << "Enter new medication name: ";
    cin.ignore();
    getline(cin, medicationName);

    cout << "Enter new dosage: ";
    getline(cin, dosage);

    cout << "Enter new frequency: ";
    getline(cin, frequency);

    cout << "Enter new notes: ";
    getline(cin, notes);

    sql = "UPDATE Prescriptions SET medicationName = ?, dosage = ?, frequency = ?, notes = ?, updatedAt = datetime('now') WHERE prescriptionId = ?";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, medicationName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, dosage.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, frequency.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, notes.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, prescriptionId);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cout << error << "Failed to update prescription." << reset << endl;
    }
    else
    {
        cout << green << "Prescription updated successfully." << reset << endl;
    }

    sqlite3_finalize(stmt);

    cout << "Press Enter to return...";
    cin.ignore();
    cin.get();
}