#pragma once

#include <sqlite3.h>
#include <iostream>
#include <vector>

void SQL(sqlite3*, const char*);
void createEnemies(sqlite3*);
sqlite3* getDatabase();