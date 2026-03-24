#pragma once

#include <sqlite3.h>

void openDatabase();
void closeDatabase();
void createTables();

extern sqlite3* db;
