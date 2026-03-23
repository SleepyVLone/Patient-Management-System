#include <iostream>
#include <string>

#include "login.h"

using namespace std;

void login()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    int back = -1;

    while (back != 0)
    {
        system("clear");

        string username;
        string password;

        cout << green << "=== Login Menu ===" << reset << endl << endl;

        cout << "Enter a username";
        cin >> username;

        cout << "Enter a password";
        cin >> password;

        if (username == "admin" && password == "1234")
        {
            cout << green << "Login successful." << reset << endl;
        }
        else
        {
            cout << error << "Login failed." << reset << endl;
        }

        cout << endl;
        cout << "Enter 0 to return to the main menu: ";
        cin >> back;
    }
}