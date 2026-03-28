#include <iostream>

#include "database.h"
#include "calculateStatistics.h"

using namespace std;

void calculateStatistics()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    sqlite3_stmt* stmt;

    //Cancer

    string sql = "SELECT AVG(p.age) FROM Patients p JOIN PatientConditions pc ON p.patientId = pc.patientId WHERE pc.conditionType = 'Cancer'";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        double avgAgeCancer = sqlite3_column_double(stmt, 0);
        cout << green << "Average age of cancer patients: " << avgAgeCancer << reset << endl;
    }
    sqlite3_finalize(stmt);

    //Diabetes

    sql = "SELECT AVG(p.age) FROM Patients p JOIN PatientConditions pc ON p.patientId = pc.patientId WHERE pc.conditionType = 'Diabetes'";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        double avgAgeDiabetes = sqlite3_column_double(stmt, 0);
        cout << green << "Average age of diabetes patients: " << avgAgeDiabetes << reset << endl;
    }
    sqlite3_finalize(stmt);

    //Smokers w/ Cancer

    sql = "SELECT COUNT(*) FROM Patients p JOIN PatientConditions pc ON p.patientId = pc.patientId WHERE pc.conditionType = 'Smoking' AND p.hasCancerHistory = 1";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int avgAgeSmokersWithCancer = sqlite3_column_int(stmt, 0);
        cout << green << "Number of smokers with cancer history: " << avgAgeSmokersWithCancer << reset << endl;
    }
    sqlite3_finalize(stmt);

    //Recovered cancer patients

    sql = "SELECT AVG(age) FROM Patients WHERE isRecoveredFromCancer = 1";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        double avgAgeCancerRecovered = sqlite3_column_double(stmt, 0);
        cout << green << "Average age of cancer patients that have recovered: " << avgAgeCancerRecovered << reset << endl;
    }
    sqlite3_finalize(stmt);

    cout << "\nPress Enter to return to menu...";

    cin.ignore();
    cin.get();
}