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
	//Get rarities
	int rarity = random(100);
	bool can = true; //temp

	if (rarity <= 1) {
		rarity = 3; //Very rare
	}
	else if (can && rarity > 1 && rarity <= 25) { //Check if can elvolve
		rarity = 2; //Rare
	}
	else {
		rarity = 1; //Common
	}

	std::string sql = std::string("SELECT * FROM ENTITIES WHERE RARITIES = " + std::to_string(rarity));
	std::vector<std::vector<std::string>> datas = dataSQL(db, sql.c_str());
	std::cout << "datas size : " << datas.size() << std::endl;

	//Get a random pokemon inside datas
	int id = random(datas.size());
	std::cout << "Pokemon choosen : " << datas[id][1] << std::endl;
	return datas[id];
}

void createDatabase(sqlite3* db) {
	//Get types
	std::string sql = std::string("SELECT * FROM TYPES");
	std::vector<std::vector<std::string>> datas = dataSQL(db, sql.c_str());

	if (!datas.size()) { //Création des données des types si la table est vide
		std::cout << "Creating types..." << std::endl;
		std::vector<std::string> types;
		/* -- Types
		* 1: Normal - 2: Water - 3: Thunder - 4: Fire - 5: Bug
		* 6: Fly
		* */
		types.push_back("\"Normal\", \"0\", \"0\"");
		types.push_back("\"Water\", \"4\", \"3\"");
		types.push_back("\"Thunder\", \"2\", \"0\"");
		types.push_back("\"Fire\", \"5\", \"2\"");
		types.push_back("\"Bug\", \"0\", \"4\"");
		types.push_back("\"Fly\", \"0\", \"3\"");

		for (size_t i = 0; i < types.size(); i++)
		{
			std::string sql = std::string(
				"INSERT INTO ENTITIES(NAME, EFFECTIVE, WEAKNESS)"\
				"VALUES(" + types[i] + ");");
			SQL(db, sql.c_str());
		}
	}
	else {
		std::cout << "Enemis already created !" << std::endl;
	}

	//Get entities
	sql = std::string("SELECT * FROM ENTITIES");
	datas = dataSQL(db, sql.c_str());

	if (!datas.size()) { //Création des données des ennemis si la table est vide
		std::cout << "Creating enemies..." << std::endl;
		std::vector<std::string> pokemon;
		/* 
		* -- Rarities
		* 1: Common - 2: Rare - 3: Very Rare
		* -- Types
		* 1: Normal - 2: Water - 3: Thunder - 4: Fire - 5: Bug
		*/
		//1[Name (100)], 2[HP int], 3[Attack int], 4[Speed int], 5[Frames int], 6[Type int], 7[Rarities int]
		pokemon.push_back("\"Arceus\", \"120\", \"120\", \"120\", \"84\", \"1\", \"3\"");
		pokemon.push_back("\"Lillipup\", \"45\", \"60\", \"55\", \"64\", \"1\", \"1\"");
		pokemon.push_back("\"Caterpie\", \"45\", \"30\", \"45\", \"41\", \"5\", \"1\"");
		pokemon.push_back("\"Pidgey\", \"40\", \"45\", \"56\", \"21\", \"6\", \"1\"");
		pokemon.push_back("\"Vulpix\", \"38\", \"41\", \"65\", \"36\", \"4\", \"1\"");
		pokemon.push_back("\"Psyduck\", \"50\", \"52\", \"55\", \"24\", \"2\", \"1\"");
		pokemon.push_back("\"Ninetales\", \"73\", \"76\", \"100\", \"27\", \"4\", \"2\"");
		//pokemon.push_back("\"Pidgey\", \"40\", \"56\", \"1\", \"21\", \"1\", \"1\"");
		//pokemon.push_back("\"Pidgey\", \"40\", \"56\", \"1\", \"21\", \"1\", \"1\"");

		for (size_t i = 0; i < pokemon.size(); i++)
		{
			std::string sql = std::string(
				"INSERT INTO ENTITIES(NAME, HP, ATTACK, SPEED, FRAMES, TYPE, RARITIES)"\
				"VALUES(" + pokemon[i] + ");");
			SQL(db, sql.c_str());
		}
	}
	else {
		std::cout << "Enemis already created !" << std::endl;
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
	* - Entities : Enemies
	* 1[Name (100)], 2[HP int], 3[Attack int], 4[Speed int], 5[Frames int], 6[Type int], 7[Rarities int]
	* - Types
	* [Name (100)], [Effective int] (Strong against), [Weakness int] (Weak against)
	*/

	sql = "CREATE TABLE IF NOT EXISTS ENTITIES(ID INTEGER PRIMARY KEY NOT NULL, NAME VARCHAR(100), HP INT, ATTACK INT, SPEED INT, FRAMES INT, TYPE INT, RARITIES INT);"\
		"CREATE TABLE IF NOT EXISTS TYPES(ID INTEGER PRIMARY KEY NOT NULL, NAME VARCHAR(100), EFFECTIVE INT, WEAKNESS INT);";

	SQL(db, sql);

	std::cout << "----------" << std::endl;

	return db;
}

int random(int range) {
	srand(time(0));
	int random = rand() % range;
	return random;
}