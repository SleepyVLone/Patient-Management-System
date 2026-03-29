#include <iostream>
#include <string>

#include "login.h"
#include "database.h"
#include "patientMenu.h"
#include "nurseMenu.h"
#include "doctorMenu.h"
#include "pharmacistMenu.h"
#include "hashPassword.h"

using namespace std;

void login()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    while(true)
    {
        string username;
        string password;

        cout << "=== Login ===" << endl << endl;

        cout << lightGreen << "Please enter your username: ";
        cin >> username;

        cout << lightGreen << "Please enter your password: ";
        cin >> password;

        if (username.empty() || password.empty()) // Validates that the username and password are not empty
        {
            cout << error << "Username and password cannot be empty." << reset << endl;

            continue;
        }

        sqlite3_stmt* stmt;

        string sql = "SELECT userId, passwordHash, role FROM Users WHERE username = ?"; //Query the database for users with matching usernames

        int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        if (result != SQLITE_OK)
        {
            cout << error << "Database error." << reset << endl;
            return;
        }

        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int userId = sqlite3_column_int(stmt, 0); //Gets the users details from the query results
            string storedHash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

            if (hashPassword(password) == storedHash)       //Compares the hashed version of the password with the stored hash. It would be better to use SHA256 + salt, but due to time constraints I went with std::hash
            {                                               //Sends the user to the correct menu depending on their role
                if (role == "Doctor") 
                    doctorMenu(userId);
                else if (role == "Nurse")
                    nurseMenu(userId);
                else if (role == "Pharmacist")
                    pharmacistMenu(userId);
                else if(role == "Patient")
                    patientMenu(userId);
                else
                {
                    cout << error << "Account does not exist or incorrect password." << reset << endl;
                    sqlite3_finalize(stmt);
                    continue;
                }
                sqlite3_finalize(stmt);
                break;
            }
            else
            {
                cout << error << "Incorrect username or password" << reset << endl; //incorrect password

                cout << "Press 0 to go back or any key to try again: ";

                string choice;
                cin >> choice;

                sqlite3_finalize(stmt);

                if (choice == "0") 
                    break;
                else continue;
            }
        }
        else
        {
            cout << error << "Incorrect username or password." << reset << endl;
            cout << "Press 0 to go back to the Main Menu or any key followed by the Enter key to try again: ";

            string choice;
            cin >> choice;
            sqlite3_finalize(stmt);

            if (choice == "0")
                break;
            else
                continue;
        }
    }
}