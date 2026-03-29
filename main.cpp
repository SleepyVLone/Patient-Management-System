#include <iostream>
#include <string>
#include <cstdlib> //used to clear the screen 

#include "mainMenu.h"
#include "database.h"

int main()
{
    openDatabase();
    mainMenu();
    closeDatabase();
    return 0;
}