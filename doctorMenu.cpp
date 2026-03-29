#include <iostream>

#include "doctorMenu.h"
#include "calculateStatistics.h"
#include "modifyMedication.h"
#include "viewPatientDetails.h"
#include "searchPatients.h"
#include "updatePatientInformation.h"

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

        cout << lightGreen << "1. Patient Lookup" << reset << endl;
        cout << lightGreen << "2. View Patient Details" << reset << endl;
        cout << lightGreen << "3. Update Patient Information" << reset << endl;
        cout << lightGreen << "4. Modify Patient Medication" << reset << endl;
        cout << lightGreen << "5. View Statistics" << reset << endl;
        cout << lightGreen << "6. Logout" << reset << endl;

        int choice;
        //Validates that the input is a number
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << error << "Invalid input. Please enter a number." << reset << endl;
            continue;
        }

        if (choice == 1)
        {
            searchPatients(); //searches for the patient by their name and provides their userId, so that they can be found in the viewPatientDetails using their provided ID
        }
        else if (choice == 2)
        {
            viewPatientDetails(); //Shows a patients full details by using their userId
        }
        else if (choice == 3)
        {
            updatePatientInformation(); //Allows the doctor to update the patients personal information
        }
        else if (choice == 4)
        {
            modifyMedication(); //Allows the doctor to add or modify a patients medication
        }
        else if (choice == 5)
        {
            calculateStatistics(); //Shows the doctor all patient stats
        }
        else if (choice == 6)
        {
            break;
        }
        else
        {
            cout << error << "Invalid selection. Please try again." << reset << endl;
        }
    }
}