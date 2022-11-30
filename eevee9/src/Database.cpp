#include "Database.h"

int callback(void* datas, int argc, char** argv, char** azColName) {
	int i;
	//On crée une variable qui va copier void* datas dans un autre type
	std::vector<std::vector<std::string>>* p_datas = static_cast<std::vector<std::vector<std::string>>*>(datas);
	std::vector<std::string> data;

	for (i = 0; i < argc; i++) {
		//On stocke chaque valeur retournée dans notre vecteur de string
		std::string element = std::string(argv[i]);
		data.push_back(element);
	}

	//On renvoie ce vecteur dans un autre vecteur contenant toutes les données
	p_datas->push_back(data);
	return 0;
}

std::vector<std::vector<std::string>> dataSQL(sqlite3* db, const char* sql) {
	std::vector<std::vector<std::string>> datas;
	char* error = 0;
	int rc = sqlite3_exec(db, sql, callback, &datas, &error);

	if (rc) {
		std::cerr << sql << "\n--> SQL error : " << error << std::endl;
	}
	else {
		std::cout << sql << "\n--> SQL done !" << std::endl;
	}

	return datas;
}

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

std::vector<std::string> getEnemy(sqlite3* db) {
	int id = random(3) + 1;
	std::string sql = std::string("SELECT * FROM ENTITIES WHERE ID = " + std::to_string(id));
	std::vector<std::vector<std::string>> datas = dataSQL(db, sql.c_str());
	return datas[0];
}

void createEnemies(sqlite3* db) {
	//Création des données des ennemis si la base de données est vide
	//Ajout condition vide
	std::vector<std::string> pokemon;
	pokemon.push_back("\"Arceus\", \"120\", \"120\", \"84\"");
	pokemon.push_back("\"Lillipup\", \"45\", \"55\", \"64\"");
	pokemon.push_back("\"Caterpie\", \"45\", \"45\", \"41\"");
	pokemon.push_back("\"Pidgey\", \"40\", \"56\", \"21\"");

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

int random(int range) {
	srand(time(0));
	int random = rand() % range;
	return random;
}