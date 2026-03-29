#include <iostream>

#include "nurseMenu.h"
#include "calculateStatistics.h"
#include "modifyMedication.h"
#include "viewPatientDetails.h"
#include "searchPatients.h"
#include "updatePatientInformation.h"

using namespace std;

void nurseMenu(int userId)
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    while (true) //Loops until nurse logs out
    {
        cout << green << "=== Nurse Menu ===" << reset << endl << endl;

        cout << lightGreen << "1. Patient Lookup" << reset << endl;
        cout << lightGreen << "2. View Patient Details" << reset << endl;
        cout << lightGreen << "3. Update Patient Information" << reset << endl;
        cout << lightGreen << "4. View Statistics" << reset << endl;
        cout << lightGreen << "5. Logout" << reset << endl;

        int choice;

        if (!(cin >> choice)) //input validation
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << error << "Invalid input. Please enter a number." << reset << endl;
            continue;
        }

        if (choice == 1)
        {
            searchPatients(); //Search for patient by name
        }
        else if (choice == 2)
        {
            viewPatientDetails(); //View full details of a patient using their userId
        }
        else if (choice == 3)
        {
            updatePatientInformation(); //Update a patients personal information
        }
        else if (choice == 4)
        {
            calculateStatistics(); //View all patients stats
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