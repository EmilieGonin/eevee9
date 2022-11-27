#pragma once

#include <sqlite3.h>
#include <iostream>

void SQL(sqlite3* db, const char* sql);
sqlite3* getDatabase();