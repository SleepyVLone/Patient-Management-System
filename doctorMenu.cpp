#include <iostream>

#include "doctorMenu.h"
#include "calculateStatistics.h"
#include "modifyMedication.h"
#include "viewPatientDetails.h"

using namespace std;

void doctorMenu(int userId)
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    while (true)
    {
        cout << green << "=== Doctor Menu ===" << reset << endl << endl;

        cout << lightGreen << "1. View Patients" << reset << endl;
        cout << lightGreen << "2. View Patient Details" << reset << endl;
        cout << lightGreen << "3. Modify Patient Medication" << reset << endl;
        cout << lightGreen << "4. View Statistics" << reset << endl;
        cout << lightGreen << "5. Logout" << reset << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            
        }
        else if (choice == 2)
        {

        }
        else if (choice == 3)
        {

        }
        else if (choice == 4)
        {
            calculateStatistics();
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            cout << error << "Invalid selection. Please try again." << reset << endl;
        }
        
    }
}