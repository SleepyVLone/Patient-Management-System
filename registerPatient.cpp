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
    cout << "Have you ever had cancer? (Yes/No): ";
    cin >> cancerHistoryInput;
    hasCancerHistory = (cancerHistoryInput == "yes");
    if (hasCancerHistory == "yes")

    cout << "have you recovered from cancer: ";
    cin >> hasRecoveredFromCancer;

    cout << "What stage of cancer do you have: ";
    cin >> cancerStage;

    cout << "What type of diabetes do you have: ";
    cin >> diabetesType;

    cout << "How often do you smoke (Daily, Weekly, Monthly): ";
    cin >> smokingFrequency;


}