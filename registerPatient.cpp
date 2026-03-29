#include <iostream>
#include <string>

#include "registerPatient.h"
#include "database.h"
#include "hashPassword.h" //used to hash passwords before they are stored in the database for security reasons

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

    while(true) //Loops until a valid username is entered
    {
        cout << "Please enter the username you would like to use: "; 
        cin >> registerUsername;

        sqlite3_stmt* checkStmt;

        string checkSql = "SELECT userId FROM Users WHERE username = ?"; //Checks if the username already exists

        sqlite3_prepare_v2(db, checkSql.c_str(), -1, &checkStmt, nullptr);
        sqlite3_bind_text(checkStmt, 1, registerUsername.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(checkStmt) == SQLITE_ROW) //This if statement runs if the username already exists in the database
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
    hasCancerHistory = (cancerHistoryInput == "yes"); //converts yes or no to a boolean

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
            hasRecoveredFromCancer = true; //If no current cancer assume user has recovered
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

    //Inserts new user into Users table
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

    int userId = sqlite3_last_insert_rowid(db); //Auto gen userId

    //Inserts patients personal details into Patients table
    sql = "INSERT INTO Patients (userId, fullName, age, hasCancerHistory, isRecoveredFromCancer) VALUES (?, ?, ?, ?, ?)";

    result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_text(stmt, 2, fullName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, age);
    sqlite3_bind_int(stmt, 4, hasCancerHistory); //bool stored as int
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

    int patientId = sqlite3_last_insert_rowid(db); //Gets auto gen patientId

    //Inserts cancer conditions if patient has cancer conditions
    if (hasCancerHistory)
    {
        sql = "INSERT INTO PatientConditions (patientId, conditionType) VALUES (?, 'Cancer')";

        result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_int(stmt, 1, patientId);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        int patientConditionId = sqlite3_last_insert_rowid(db);

        //inserts cancer stage into CancerDetails table
        sql = "INSERT INTO CancerDetails (patientConditionId, cancerStage) VALUES (?, ?)";

        result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_int(stmt, 1, patientConditionId);
        sqlite3_bind_int(stmt, 2, cancerStage);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    if (hasDiabetes) //Inserts diabetes if patient has diabetes 
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

    if (smokingInput == "yes") //Inserts smoking conditions if patient smokes
    {
        sql = "INSERT INTO PatientConditions (patientId, conditionType) VALUES (?, 'Smoking')";

        result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_int(stmt, 1, patientId);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        int patientConditionId = sqlite3_last_insert_rowid(db);

        //Inserts smoking frequency into SmokingDetails table
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