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

    while (true) //Loops until the pharmacist logs out
    {
        cout << green << "=== Pharmacist Menu ===" << reset << endl << endl;

        cout << lightGreen << "1. View Patients" << reset << endl;
        cout << lightGreen << "2. View Patient Details" << reset << endl;
        cout << lightGreen << "3. View Prescriptions" << reset << endl;
        cout << lightGreen << "4. Edit Prescriptions" << reset << endl;
        cout << lightGreen << "5. Create Pharmacist Account" << reset << endl;
        cout << lightGreen << "6. Logout" << reset << endl;

        int choice;

        if (!(cin >> choice)) //Input validation
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << error << "Invalid input. Please enter a number." << reset << endl;
            continue;
        }

        if (choice == 1)
        {
            searchPatients(); //Search for a patient using their name
        }
        else if (choice == 2)
        {
            viewPatientDetails(); //View a patients full deatils
        }
        else if (choice == 3)
        {
            viewPrescriptions(); //View all prescriptions relevant to a patient
        }
        else if (choice == 4)
        {
            editPrescriptions(); //Edit a prescription for a patient
        }
        else if (choice == 5)
        {
            createPharmacistAccount(); //create a pharmacist account for another pharmacist. Only pharmacists can do this
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