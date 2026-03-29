#include <iostream>
#include <string>

#include "registerPatient.h"
#include "database.h"
#include "hashPassword.h"

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

    while(true)
    {
        cout << "Please enter the username you would like to use: ";
        cin >> registerUsername;

        sqlite3_stmt* checkStmt;

        string checkSql = "SELECT userId FROM Users WHERE username = ?";

        sqlite3_prepare_v2(db, checkSql.c_str(), -1, &checkStmt, nullptr);
        sqlite3_bind_text(checkStmt, 1, registerUsername.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(checkStmt) == SQLITE_ROW)
        {
            cout << error << "Username already taken. Please choose another." << reset << endl;
            sqlite3_finalize(checkStmt);
            continue;
        }

        sqlite3_finalize(checkStmt);
        break;
    }

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

    sqlite3_bind_text(stmt, 1, registerUsername.c_str(), -1, SQLITE_STATIC);    //Binds the username to the first ?
    
    string hashedPassword = hashPassword(registerPassword);                     //Hashes the password before storing it in the database
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);      //Binds the hashed password to the second ?

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cout << error << "Username already taken." << reset << endl;
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);

    cout << green << "Your account has been successfully registered." << reset << endl;

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

    int patientId = sqlite3_last_insert_rowid(db);

    if (hasCancerHistory)
    {
        sql = "INSERT INTO PatientConditions (patientId, conditionType) VALUES (?, 'Cancer')";

        result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_int(stmt, 1, patientId);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        int patientConditionId = sqlite3_last_insert_rowid(db);

        sql = "INSERT INTO CancerDetails (patientConditionId, cancerStage) VALUES (?, ?)";

        result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_int(stmt, 1, patientConditionId);
        sqlite3_bind_int(stmt, 2, cancerStage);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    if (hasDiabetes)
    {
        sql = "INSERT INTO PatientConditions (patientId, conditionType) VALUES (?, 'Diabetes')";

        result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_int(stmt, 1, patientId);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        int patientConditionId = sqlite3_last_insert_rowid(db);

        sql = "INSERT INTO DiabetesDetails (patientConditionId, diabetesType) VALUES (?, ?)";

        result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_int(stmt, 1, patientConditionId);
        sqlite3_bind_int(stmt, 2, diabetesType);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    if (smokingInput == "yes")
    {
        sql = "INSERT INTO PatientConditions (patientId, conditionType) VALUES (?, 'Smoking')";

        result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_int(stmt, 1, patientId);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        int patientConditionId = sqlite3_last_insert_rowid(db);

        sql = "INSERT INTO SmokingDetails (patientConditionId, smokingFrequency) VALUES (?, ?)";

        result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_int(stmt, 1, patientConditionId);
        sqlite3_bind_text(stmt, 2, smokingFrequency.c_str(), -1, SQLITE_STATIC);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    cout << green << "Registration complete! You can now log in." << reset << endl;
    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}