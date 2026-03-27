#include <iostream>

#include "patientMenu.h"
#include "viewMyRecord.h"
#include "calculateTreatmentCosts.h"

using namespace std;

void patientMenu(int userId)
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    while (true)
    {
        cout << lightGreen << "=== Patient Menu ===" << reset << endl << endl;

        cout << green << "1. View My Medical Record" << reset << endl;
        cout << green << "2. View My Treatment Costs" << reset << endl;
        cout << green << "3. Logout" << reset << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            viewMyRecord(userId);
        }
        else if (choice == 2)
        {
            calculateTreatmentCosts(userId);
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << error << "Invalid selection. Please try again." << reset << endl;
        }
    }
}