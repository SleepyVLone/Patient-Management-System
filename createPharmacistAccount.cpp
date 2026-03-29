#include <iostream>

#include "createPharmacistAccount.h"
#include "database.h"
#include "hashPassword.h" //Function for hashing the password before storinng it in the database

using namespace std;

void createPharmacistAccount()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    string username;
    string password;

    cout << green << "=== Create Pharmacist Account ===" << reset << endl << endl;

    //Check username uniqueness loop
    while (true)
    {
        cout << "Enter username: ";
        cin >> username;

        sqlite3_stmt* checkStmt;

        string checkSql = "SELECT userId FROM Users WHERE username = ?"; //Used to check if the username is unique 

        sqlite3_prepare_v2(db, checkSql.c_str(), -1, &checkStmt, nullptr);
        sqlite3_bind_text(checkStmt, 1, username.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(checkStmt) == SQLITE_ROW) //This checks if the username is unique and if it is not runs the if statement below
        {
            cout << error << "Username already taken. Please choose another." << reset << endl;
            sqlite3_finalize(checkStmt);
            continue;
        }
        sqlite3_finalize(checkStmt);
        break;
    }

    cout << "Enter password: ";
    cin >> password;

    sqlite3_stmt* stmt;
    //Adds a new pharmacist account with a hashed password, so that the account is secure
    string sql = "INSERT INTO Users (username, passwordHash, role, createdAt) VALUES (?, ?, 'Pharmacist', datetime('now'))";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    string hashedPassword = hashPassword(password); //hashes the password before storing it
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cout << error << "Failed to create account." << reset << endl;
    }
    else
    {
        cout << green << "Pharmacist account created successfully." << reset << endl;
    }

    sqlite3_finalize(stmt);
    
    cout << "\nPress Enter to return...";
    cin.ignore();
    cin.get();
}