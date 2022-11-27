#include "Database.h"
#include <iostream>

void SQL(sqlite3* db, const char* sql) {
	char* error;
	int rc = sqlite3_exec(db, sql, NULL, NULL, &error);

	if (rc) {
		std::cerr << sql << "\n--> SQL error : " << error << std::endl;
	}
	else {
		std::cout << sql << "\n--> SQL done !" << std::endl;
	}
}

sqlite3* getDatabase() {
	sqlite3* db;
	const char* sql;
	int rc = sqlite3_open("eevee9.db", &db);

	if (rc) {
		std::cerr << "Can't open database !" << std::endl;
	}
	else {
		std::cout << "Opened database successfully !" << std::endl;
	}

	std::cout << "Loading tables..." << std::endl;

	sql = "CREATE TABLE IF NOT EXISTS ENTITIES(ID INTEGER PRIMARY KEY NOT NULL, NAME VARCHAR(100));";

	SQL(db, sql);

	std::cout << "----------\n";

	return db;
}