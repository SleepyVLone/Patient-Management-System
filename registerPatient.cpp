#include <iostream>
#include <string>

#include "registerPatient.h"
#include "database.h"

using namespace std;

void registerPatient()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    system ("clear");

    string registerUsername;
    string registerPassword;

    string fullName;
    int age;
    bool hasCancerHistory;
    bool hasRecoveredFromCancer;
    int cancerStage;
    int diabetesType;
    string smokingFrequency;
    string conditionType;
    bool hasDiabetes;

    cout << "Please enter the username you would like to use: ";
    cin >> registerUsername;

    cout << "Please enter the password for your account: ";
    cin >> registerPassword;

    cout << "Thank you!" << endl;
    cout << "We are now going to ask you some questions to complete your account." << endl << endl;

    cout << "Please enter your full name: ";
    cin.ignore();
    getline(cin, fullName);

    cout << "Please enter your age: ";
    cin >> age;

    string cancerHistoryInput;
    cout << "Have you ever had cancer? (yes/no): ";
    cin >> cancerHistoryInput;
    hasCancerHistory = (cancerHistoryInput == "yes");

    if (hasCancerHistory)
    {
        string currentCancerInput;
        cout << "Do you currently have cancer? (yes/no): ";
        cin >> currentCancerInput;

        if (currentCancerInput == "yes")
        {
            hasRecoveredFromCancer = false;
            cout << "What stage of cancer do you have? (1-4): ";
            cin >> cancerStage;
        }
        else
        {
            hasRecoveredFromCancer = true;
        }
    }

    string hasDiabetesInput;
    cout << "Do you have diabetes? (yes/no): ";
    cin >> hasDiabetesInput;
    hasDiabetes = (hasDiabetesInput == "yes");

    if (hasDiabetes)
    {
        cout << "What type of diabetes do you have? (1-2): ";
        cin >> diabetesType;
    }

    string smokingInput;
    cout << "Do you smoke? (yes/no): ";
    cin >> smokingInput;
    if (smokingInput == "yes")
    {
        cout << "How often? (Daily/Weekly/Monthly): ";
        cin >> smokingFrequency;
    }

    sqlite3_stmt* stmt;
    string sql = "INSERT INTO Users (username, passwordHash, role, createdAt) VALUES (?, ?, 'Patient', datetime('now'))";

    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, registerUsername.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, registerPassword.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        cout << green << "Your account has been successfully registered." << reset << endl;
    }
    else
    {
        cout << error << "Account registration failed." << reset << endl;
    }
    sqlite3_finalize(stmt);

    int userId = sqlite3_last_insert_rowid(db);

    sql = "INSERT INTO Patients (userId, fullName, age, hasCancerHistory, isRecoveredFromCancer) VALUES (?, ?, ?, ?, ?)";

    result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_text(stmt, 2, fullName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, age);
    sqlite3_bind_int(stmt, 4, hasCancerHistory);
    sqlite3_bind_int(stmt, 5, hasRecoveredFromCancer);

    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        cout << green << "Patient record created." << reset << endl;
    }
    else
    {
        cout << error << "Failed to create patient record." << reset << endl;
    }
    sqlite3_finalize(stmt);
}