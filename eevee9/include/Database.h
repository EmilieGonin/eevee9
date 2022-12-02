#pragma once

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>

int callback(void*, int, char**, char**);
std::vector<std::vector<std::string>> dataSQL(sqlite3*, const char*);
void SQL(sqlite3*, const char*);
std::vector<std::string> getType(sqlite3*, int);
std::vector<std::string> getEnemy(sqlite3*);
std::vector<std::string> getSave(sqlite3*);
//1[HP int], 2[Waterstone], 3[Thunderstone], 4[Firestone], 5[Map],
//6[x], 7[y], 8[Orientation int], 9[Money]
void setSave(sqlite3*, int, int, int, int, int, int, int, int, int);
std::vector<std::string> getPlayer(sqlite3*);
void createDatabase(sqlite3*);
sqlite3* getDatabase();
int random(int);