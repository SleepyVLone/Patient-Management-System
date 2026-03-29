#include <iostream>

#include "pharmacistMenu.h"
#include "viewPrescriptions.h"
#include "editPrescriptions.h"
#include "createPharmacistAccount.h"
#include "searchPatients.h"
#include "viewPatientDetails.h"

using namespace std;

void pharmacistMenu(int userId)
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    while (true)
    {
        cout << green << "=== Pharmacist Menu ===" << reset << endl << endl;

        cout << lightGreen << "1. View Patients" << reset << endl;
        cout << lightGreen << "2. View Patient Details" << reset << endl;
        cout << lightGreen << "3. View Prescriptions" << reset << endl;
        cout << lightGreen << "4. Edit Prescriptions" << reset << endl;
        cout << lightGreen << "5. Create Pharmacist Account" << reset << endl;
        cout << lightGreen << "6. Logout" << reset << endl;

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
            viewPrescriptions();
        }
        else if (choice == 4)
        {
            
        }
        else if (choice == 5)
        {
            createPharmacistAccount();
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