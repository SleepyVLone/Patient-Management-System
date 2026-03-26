#include <iostream>
#include <string>

#include "registerPatient.h"
#include "database.h"

using namespace std;

void registerPatient()
{
    string green = "\033[32m";
    string lightGreen = "\033[92m";
    string reset = "\033[0m";
    string error = "\033[31m";

    system ("clear");

    string registerUsername;
    string registerPassword;

    string fullName;
    int age;
    bool hasCancerHistory;
    bool hasRecoveredFromCancer;
    int cancerStage;
    int diabetesType;
    string smokingFrequency;
    string conditionType;
    bool hasDiabetes;

    cout << "Please enter the username you would like to use: ";
    cin >> registerUsername;

    cout << "Please enter the password for your account: ";
    cin >> registerPassword;

    cout << "Thank you!" << endl;
    cout << "We are now going to ask you some questions to complete your account." << endl << endl;

    cout << "Please enter your full name: ";
    cin.ignore();
    getline(cin, fullName);

    cout << "Please enter your age: ";
    cin >> age;

    string cancerHistoryInput;
    cout << "Have you ever had cancer? (yes/no): ";
    cin >> cancerHistoryInput;
    hasCancerHistory = (cancerHistoryInput == "yes");

    if (hasCancerHistory)
    {
        string currentCancerInput;
        cout << "Do you currently have cancer? (yes/no): ";
        cin >> currentCancerInput;

        if (currentCancerInput == "yes")
        {
            hasRecoveredFromCancer = false;
            cout << "What stage of cancer do you have? (1-4): ";
            cin >> cancerStage;
        }
        else
        {
            hasRecoveredFromCancer = true;
        }
    }

    string hasDiabetesInput;
    cout << "Do you have diabetes? (yes/no): ";
    cin >> hasDiabetesInput;
    hasDiabetes = (hasDiabetesInput == "yes");

    if (hasDiabetes)
    {
        cout << "What type of diabetes do you have? (1-2): ";
        cin >> diabetesType;
    }

    string smokingInput;
    cout << "Do you smoke? (yes/no): ";
    cin >> smokingInput;
    if (smokingInput == "yes")
    {
        cout << "How often? (Daily/Weekly/Monthly): ";
        cin >> smokingFrequency;
    }
}