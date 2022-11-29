#include "Database.h"

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

void createEnemies(sqlite3* db) {
	//Création des données des ennemis
	std::vector<std::string> pokemon;
	pokemon.push_back("Name, 50, 50, 50");
	pokemon.push_back("Name2, 50, 50, 50");
	pokemon.push_back("Name3, 50, 50, 50");
	pokemon.push_back("Name4, 50, 50, 50");

	//Récupération des ennemis
	for (size_t i = 0; i < pokemon.size(); i++)
	{
		std::string sql = std::string(
			"INSERT INTO ENTITIES(NAME, HP, SPEED, FRAMES)"\
			"VALUES(" + pokemon[i] + ");");
		SQL(db, sql.c_str());
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

	/* ----Tables----
	* - Entities : Eevee [ID 0] + Enemies
	* [Name (100)], [HP int], [Speed int], [Frames int]
	*/
	sql = "CREATE TABLE IF NOT EXISTS ENTITIES(ID INTEGER PRIMARY KEY NOT NULL, NAME VARCHAR(100), HP INT, SPEED INT, FRAMES INT);";

	SQL(db, sql);

	std::cout << "----------" << std::endl;

	return db;
}