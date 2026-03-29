#include <iostream>

#include "searchPatients.h"
#include "database.h"

using namespace std;

void searchPatients()
{
    sqlite3_stmt* stmt;

    string sql = "SELECT patientId, fullName, age FROM Patients WHERE fullName LIKE ?";

    string searchTerm;

    cout << "Enter patient name to search: ";
    cin.ignore();
    getline(cin, searchTerm);

    string searchPattern = "%" + searchTerm + "%";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, searchPattern.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int patientId = sqlite3_column_int(stmt, 0);
        string fullName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int age = sqlite3_column_int(stmt, 2);
        cout << "ID: " << patientId << " | Name: " << fullName << " | Age: " << age << endl;
    }

    sqlite3_finalize(stmt);

    cout << "\nPress Enter to return...";
    cin.ignore();
    cin.get();
}