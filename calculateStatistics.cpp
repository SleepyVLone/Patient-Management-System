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

    sqlite3_stmt* stmt;     //Used to prepare and run SQL queries

    //Cancer
    //AVG calculates the average age of all patients with cancer
    //Links Patients and PatientConditions together using patientId
    string sql = "SELECT AVG(p.age) FROM Patients p JOIN PatientConditions pc ON p.patientId = pc.patientId WHERE pc.conditionType = 'Cancer'";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr); //Prepares the SQL query so it can be ran/turns the SQL into a prepared statement

    if (sqlite3_step(stmt) == SQLITE_ROW) //SQLITE_ROW runs the following if statement if a result was found
    {
        double avgAgeCancer = sqlite3_column_double(stmt, 0); //0 = the column place/the average age is in column 0
        cout << green << "Average age of cancer patients: " << avgAgeCancer << reset << endl;
    }
    sqlite3_finalize(stmt); //release the prepared statement from the memory

    //Diabetes
    //Everything is the same as cancer here, but for diabetes
    sql = "SELECT AVG(p.age) FROM Patients p JOIN PatientConditions pc ON p.patientId = pc.patientId WHERE pc.conditionType = 'Diabetes'";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        double avgAgeDiabetes = sqlite3_column_double(stmt, 0);
        cout << green << "Average age of diabetes patients: " << avgAgeDiabetes << reset << endl;
    }
    sqlite3_finalize(stmt);

    //Smokers w/ Cancer
    //COUNT(*) Shows the number of matching rows
    //hasCancerHistory = 1 means only patients with cancer history/a filter to add patients with cancer history
    sql = "SELECT COUNT(*) FROM Patients p JOIN PatientConditions pc ON p.patientId = pc.patientId WHERE pc.conditionType = 'Smoking' AND p.hasCancerHistory = 1";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int avgAgeSmokersWithCancer = sqlite3_column_int(stmt, 0);
        cout << green << "Number of smokers with cancer history: " << avgAgeSmokersWithCancer << reset << endl;
    }
    sqlite3_finalize(stmt);

    //Recovered cancer patients
    // isRecoveredFromCancer = 1 means only show patients who have recovered
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