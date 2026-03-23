#include <iostream>
#include <string>

#include "registerPatient.h"

using namespace std;

void registerPatient()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    system ("clear");

    string registerAccount;
    string registerPassword;

    cout << green << "=== Register Menu ===" << reset << endl << endl;

    cout << lightGreen << "Enter account name: " << reset;
    cin >> registerAccount;

    cout << lightGreen << "Enter account password: " << reset;
    cin >> registerPassword;

    cout << endl;
    cout << green << "Account has been registered successfully." << reset << endl;

    cout << endl;
    cout << "Enter 0 to return to the main menu: ";

    int back;
    cin >> back;
}