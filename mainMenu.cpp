#include <iostream>

#include "mainMenu.h"
#include "login.h"
#include "registerPatient.h"

using namespace std;

void mainMenu()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    int choice = 0;

    while (choice !=3)
    {
        system("clear");

        cout << green << "=== Healthcare System ===" << reset << endl << endl;
        cout << lightGreen << "Please make a selection" << endl << endl;

        cout << lightGreen << "1. Login" << reset << endl;
        cout << lightGreen << "2. Register" << reset << endl;
        cout << lightGreen << "3. Exit" << reset << endl;

        cin >> choice;

        if (choice == 1)
        {
            login();
        }
        else if (choice == 2)
        {
            registerPatient();
        }
        else if (choice == 3)
        {
            cout << green << "Exiting Program..." << reset << endl;
        }
        else
        {
            cout << error << "Invalid selection, please try again." << endl;
            cin.ignore();
            cin.get();
        }
    }
}