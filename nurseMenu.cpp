#include <iostream>

#include "nurseMenu.h"
#include "calculateStatistics.h"
#include "modifyMedication.h"
#include "viewPatientDetails.h"
#include "searchPatients.h"
#include "viewPatientDetails.h"
#include "updatePatientInformation.h"

using namespace std;

void nurseMenu(int userId)
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    while (true)
    {
        cout << green << "=== Nurse Menu ===" << reset << endl << endl;

        cout << lightGreen << "1. Patient Lookup" << reset << endl;
        cout << lightGreen << "2. View Patient Details" << reset << endl;
        cout << lightGreen << "3. Update Patient Information" << reset << endl;
        cout << lightGreen << "4. View Statistics" << reset << endl;
        cout << lightGreen << "5. Logout" << reset << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            searchPatients();
        }
        else if (choice == 2)
        {
            viewPatientDetails();
        }
        else if (choice == 3)
        {
            updatePatientInformation();
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