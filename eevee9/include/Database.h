#pragma once

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>

int callback(void* datas, int argc, char** argv, char** azColName);
std::vector<std::vector<std::string>> dataSQL(sqlite3* db, const char* sql);
void SQL(sqlite3*, const char*);
std::vector<std::string> getEnemy(sqlite3*);
void createDatabase(sqlite3*);
sqlite3* getDatabase();
int random(int range);