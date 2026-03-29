#include <iostream>
#include <functional>
#include <string>

#include "hashPassword.h"

using namespace std;

string hashPassword(const string& password)
{
    hash<string> hasher;
    size_t hashValue = hasher(password);    //Generates a hash value from the password provided by the user
    return to_string(hashValue);            //Converts the hash to a string
}
