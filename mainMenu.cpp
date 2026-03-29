#include <iostream>
#include <cstdlib> //Used for system("clear") to clear the terminal 

#include "mainMenu.h"
#include "login.h"
#include "registerPatient.h"

using namespace std;

void mainMenu()
{
    //ANSI colour codes for colours in the terminal
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    int choice = 0;

    while (choice !=3) //Loop until the user selects exit
    {
        system("clear");

        cout << green << "=== Healthcare System ===" << reset << endl << endl;

        cout << lightGreen << "1. Login" << reset << endl;
        cout << lightGreen << "2. Register" << reset << endl;
        cout << lightGreen << "3. Exit" << reset << endl;

        cout << lightGreen << "Please make a selection: ";
        if (!(cin >> choice)) //Handles any inputs that aren't numbers
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << error << "Invalid input. Please enter a number." << reset << endl;
            continue;
        }

        if (choice == 1)
        {
            login(); //Goes to the login function
        }
        else if (choice == 2)
        {
            registerPatient(); //Goes to the patient registration function
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