#include <iostream>
#include <iomanip> //Used to set precision of calculations to 2 decimal places

#include "database.h"
#include "calculateTreatmentCosts.h"

using namespace std;

void calculateTreatmentCosts(int userId)
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    sqlite3_stmt* stmt;

    string sql = "SELECT conditionType FROM PatientConditions WHERE patientId = (SELECT patientId FROM Patients WHERE userId = ?)"; //finds the patientId linked to the logged in userId

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, userId);

    double totalDailyGBP = 0; //Adds up the daily cost for all conditions

    while (sqlite3_step(stmt) == SQLITE_ROW) //Loop through each condition the patient has
    {
        string conditionType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); //Gets the text from SQLite and turns it into a C++ string

        if (conditionType == "Cancer")
        {
            sqlite3_stmt* stageStmt;

            string stageSql = "SELECT cancerStage FROM CancerDetails WHERE patientConditionId = (SELECT patientConditionId FROM PatientConditions WHERE patientId = (SELECT patientId FROM Patients WHERE userId = ?) AND conditionType = 'Cancer')";

            sqlite3_prepare_v2(db, stageSql.c_str(), -1, &stageStmt, nullptr);
            sqlite3_bind_int(stageStmt, 1, userId);

            if (sqlite3_step(stageStmt) == SQLITE_ROW)
            {
                int cancerStage = sqlite3_column_int(stageStmt, 0);
                if (cancerStage == 1) totalDailyGBP += 357.14;
                else if (cancerStage == 2) totalDailyGBP += 714.29;
                else if (cancerStage == 3) totalDailyGBP += 1428.57;
            }
            sqlite3_finalize(stageStmt);
        }
        else if (conditionType == "Diabetes")
        {
            sqlite3_stmt* diabStmt;
            //Finds the diabetes type for the patient
            string diabSql = "SELECT diabetesType FROM DiabetesDetails WHERE patientConditionId = (SELECT patientConditionId FROM PatientConditions WHERE patientId = (SELECT patientId FROM Patients WHERE userId = ?) AND conditionType = 'Diabetes')";

            sqlite3_prepare_v2(db, diabSql.c_str(), -1, &diabStmt, nullptr);
            sqlite3_bind_int(diabStmt, 1, userId);

            if (sqlite3_step(diabStmt) == SQLITE_ROW)
            {
                int diabetesType = sqlite3_column_int(diabStmt, 0);

                if (diabetesType == 1) 
                {
                    totalDailyGBP += 15.04;
                }
                else if (diabetesType == 2) 
                {
                    totalDailyGBP += 7.52;
                }
            }

            sqlite3_finalize(diabStmt);
        }
        else if (conditionType == "Smoking")
        {
            sqlite3_stmt* smokStmt;
            //Finds the smoking frequency for the patient
            string smokSql = "SELECT smokingFrequency FROM SmokingDetails WHERE patientConditionId = (SELECT patientConditionId FROM PatientConditions WHERE patientId = (SELECT patientId FROM Patients WHERE userId = ?) AND conditionType = 'Smoking')";

            sqlite3_prepare_v2(db, smokSql.c_str(), -1, &smokStmt, nullptr);
            sqlite3_bind_int(smokStmt, 1, userId);

            if (sqlite3_step(smokStmt) == SQLITE_ROW)
            {
                string freq = reinterpret_cast<const char*>(sqlite3_column_text(smokStmt, 0)); //Gets the text from SQLite and turns it into a C++ string

                if (freq == "Daily") 
                {
                    totalDailyGBP += 3.64;
                }
                else if (freq == "Weekly") 
                {
                    totalDailyGBP += 1.41;
                }
                else if (freq == "Monthly") 
                {
                    totalDailyGBP += 0.70;
                }
            }

            sqlite3_finalize(smokStmt); //Releases the main prepared statement from the memory 
        }
    }

    sqlite3_finalize(stmt);

    double totalWeeklyGBP = totalDailyGBP * 7;
    double totalMonthlyGBP = totalDailyGBP * 30;
    double totalYearlyGBP = totalDailyGBP * 365;
    double exchangeRate = 1.27;

    cout << green << "\n=== Treatment Costs ===" << reset << endl << endl;

    cout.imbue(locale("en_US.UTF-8")); //Adds commas to outputs
    cout << fixed << setprecision(2) << green << "Daily:   GBP £" << totalDailyGBP << " | USD $" << totalDailyGBP * exchangeRate << reset << endl;
    cout << fixed << setprecision(2) << green << "Weekly:  GBP £" << totalWeeklyGBP << " | USD $" << totalWeeklyGBP * exchangeRate << reset << endl;
    cout << fixed << setprecision(2) << green << "Monthly: GBP £" << totalMonthlyGBP << " | USD $" << totalMonthlyGBP * exchangeRate << reset << endl;
    cout << fixed << setprecision(2) << green << "Yearly:  GBP £" << totalYearlyGBP << " | USD $" << totalYearlyGBP * exchangeRate << reset << endl << endl;

    cout << "Press Enter to return to menu...";

    cin.ignore();
    cin.get();
}