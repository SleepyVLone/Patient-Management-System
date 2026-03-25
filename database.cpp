#include <iostream>

#include "database.h"

using namespace std;

sqlite3* db = nullptr;

void openDatabase()
{
    int opnResult = sqlite3_open("nhs.db", &db);

    if (opnResult != SQLITE_OK) 
    {
        cout << "Database failed to open." << endl;
    }
    else
    {
        cout << "Database opened!" << endl;
        createTables();
    }
}

void closeDatabase()
{
    int clDatabase = sqlite3_close(db);

    if (clDatabase != SQLITE_OK)
    {
        cout << "Database failed to close." << endl;
    }
    else
    {
        cout << "Database successfully closed!" << endl;
    }
}

void createTables()
{
    //==========USERS==========

    string sql = "CREATE TABLE IF NOT EXISTS Users ("
                 "userId INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "username VARCHAR(50) UNIQUE NOT NULL,"
                 "passwordHash VARCHAR(255) NOT NULL,"
                 "role VARCHAR(20) NOT NULL,"
                 "createdAt DATETIME NOT NULL)";

    int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

    if (result != SQLITE_OK)
        {
            cout << "Failed to create tables." << endl;
        }
        else
        {
            cout << "Tables created." << endl;
        }
    
    //==========PATIENTS==========

    sql = "CREATE TABLE IF NOT EXISTS Patients ("
                 "patientId INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "userId INTEGER NOT NULL,"
                 "fullName VARCHAR(100) NOT NULL,"
                 "age INTEGER NOT NULL,"
                 "hasCancerHistory BOOLEAN NOT NULL,"
                 "isRecoveredFromCancer BOOLEAN NOT NULL)";

    result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

    if (result != SQLITE_OK)
        {
            cout << "Failed to create tables." << endl;
        }
        else
        {
            cout << "Tables created." << endl;
        }

    //==========PATIENT CONDITIONS==========

    sql = "CREATE TABLE IF NOT EXISTS PatientConditions ("
      "patientConditionId INTEGER PRIMARY KEY AUTOINCREMENT,"
      "patientId INTEGER NOT NULL,"
      "conditionType VARCHAR(20) NOT NULL)";

    result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

    if (result != SQLITE_OK)
        {
            cout << "Failed to create tables." << endl;
        }
        else
        {
            cout << "Tables created." << endl;
        }

    //==========CANCER DETAILS==========

    sql = "CREATE TABLE IF NOT EXISTS CancerDetails ("
          "patientConditionId INTEGER PRIMARY KEY,"
          "cancerStage INTEGER NOT NULL)";

    result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

    if (result != SQLITE_OK)
        {
            cout << "Failed to create tables." << endl;
        }
        else
        {
            cout << "Tables created." << endl;
        }

    //==========DIABETES DETAILS==========

    sql = "CREATE TABLE IF NOT EXISTS DiabetesDetails ("
          "patientConditionId INTEGER PRIMARY KEY,"
          "diabetesType INTEGER NOT NULL)";

    result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

    if (result != SQLITE_OK)
        {
            cout << "Failed to create tables." << endl;
        }
        else
        {
            cout << "Tables created." << endl;
        }

    //==========SMOKING DETAILS==========

    sql = "CREATE TABLE IF NOT EXISTS SmokingDetails ("
          "patientConditionId INTEGER PRIMARY KEY,"
          "smokingFrequency VARCHAR(20) NOT NULL)";

    result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

    if (result != SQLITE_OK)
        {
            cout << "Failed to create tables." << endl;
        }
        else
        {
            cout << "Tables created." << endl;
        }

    //==========PRESCRIPTIONS==========

    sql = "CREATE TABLE IF NOT EXISTS Prescriptions ("
          "prescriptionId INTEGER PRIMARY KEY AUTOINCREMENT,"
          "patientId INTEGER NOT NULL,"
          "medicationName VARCHAR(100) NOT NULL,"
          "dosage VARCHAR(50) NOT NULL,"
          "frequency VARCHAR(50) NOT NULL,"
          "notes VARCHAR(255),"
          "updatedByUserId INTEGER NOT NULL,"
          "updatedAt DATETIME NOT NULL)";

    result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

    if (result != SQLITE_OK)
        {
            cout << "Failed to create tables." << endl;
        }
        else
        {
            cout << "Tables created." << endl;
        }
}

