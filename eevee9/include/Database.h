#pragma once

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>

int callback(void*, int, char**, char**);
std::vector<std::vector<std::string>> dataSQL(sqlite3*, const char*);
void SQL(sqlite3*, const char*);

//1: Normal - 2: Water - 3: Thunder - 4: Fire - 5: Bug
//6: Fly
//1[Name(100)] , 2[Effective], 3[Weakness], 4[Affect]
std::vector<std::string> getType(sqlite3*, int);

//1[Name (100)], 2[HP int], 3[Attack int], 4[Speed int]
// 5[Frames int], 6[Type int], 7[Rarities int], 8[x], 9[y]
std::vector<std::string> getEnemy(sqlite3*, bool);

std::vector<std::string> getSave(sqlite3*);

//1[HP int], 2[Waterstone], 3[Thunderstone], 4[Firestone], 5[Map],
//6[x], 7[y], 8[Orientation int], 9[Money], 10[Step]
void setSave(sqlite3*, int, int, int, int, int, int, int, int, int, int);

//1[Name(100)], 2[HP int], 3[Attack int], 4[Speed int]
//5[Frames int], 6[Type int]
std::vector<std::string> getPlayer(sqlite3*, int);
void createDatabase(sqlite3*);
sqlite3* getDatabase();
int random(int);