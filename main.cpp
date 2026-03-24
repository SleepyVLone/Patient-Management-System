#include <iostream>
#include <string>
#include <cstdlib>

#include "mainMenu.h"
#include "database.h"

int main()
{
    openDatabase();
    mainMenu();
    closeDatabase();
    return 0;
}