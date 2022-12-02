#include "Battle.h"

Battle::Battle(Game* game, Eevee* eevee, Enemy* enemy, Interface* interface) {
	this->_eevee = eevee;
	this->_enemy = enemy;
	this->_game = game;
	this->interface = interface;
	
	this->music.setLoop(true);
	this->music.setVolume(8);
	this->lowMusic.setLoop(true);
	this->lowMusic.setVolume(8);

	this->reset();
}

Battle::~Battle() {};

void Battle::reset() {
	this->_win = this->_loose = this->_escape = this->_caught = false;
	this->_choice = this->_choosen_attack = this->_enemy_choice = 0;
	this->_turn = 1;
	this->_enemy->set(this->_eevee->canEvolve());
	this->_positionSaved = false;
}

void Battle::end() {
	std::cout << "BATTLE ENDED" << std::endl;
	std::cout << "----------" << std::endl << std::endl;
	if (this->_eevee->isEvolved()) {
		this->_eevee->set(0);
	}

	if (this->_win) {
		
		this->lowMusic.stop();

		if(this->music.getVolume() == 0)
		{
			int goalVolume = 8;
			int volume = 0;
			while(volume != goalVolume)
			{
				volume++;
				this->music.setVolume(volume);
			}
		}
		this->interface->displayComment(this->_enemy->getName() + " fainted...", this->_win - 1);
		this->music.stop();
		this->interface->displayComment("You win", this->_win);
		this->loot();
	}
	else if (this->_loose) {
		std::cout << "You loose..." << std::endl;
		this->_eevee->setHP(this->_eevee->getMaxHP());
		this->_enemy->setHP(this->_enemy->getMaxHP());
		this->interface->setMap(1); //reset eevee and puts it at his spawn
	}

	if (this->music.getStatus() == 2) {
		this->music.stop();
		this->lowMusic.stop();
	}

	this->_eevee->spritePosition(this->_eevee->getMapPosition().x, this->_eevee->getMapPosition().y);
	this->_eevee->setCoords(0, 30, 28, 3);
	this->_enemy->reset();
	this->reset();
}

void Battle::loot() {
	int loot = this->random(6);
	std::cout << "Getting loot : " << loot << std::endl;

	if (loot > 3) {
		this->_eevee->addLoot(loot - 3, 0);
		this->interface->displayComment("You got a shard !", this->_win);
	}
	this->_eevee->addLoot(0,100);
	this->interface->displayComment("You won 100$", this->_win);
}

bool Battle::battle() {
	//Music
	float percent = 20.0 / 100.0;

	if (this->music.getStatus() != 2) {
		if (this->_eevee->getHP() < percent * this->_eevee->getMaxHP()) {
			std::cout << "je suis low";
			this->music.setVolume(0);

			if (this->lowMusic.getStatus() != 2) {
				this->lowMusic.openFromFile("./sfx/Music/lowHp.wav");
				this->lowMusic.play();
			}
		}
		else {
			this->music.setVolume(8);
		}

		this->music.openFromFile(musicTab[this->random(4)]);
		this->music.play();
	}

	if (!this->_positionSaved) {
		std::cout << "Eevee map position saved !" << std::endl;
		this->_eevee->setMapPosition(this->_eevee->getSprite(2, 2).getPosition());
		this->_positionSaved = true;
	}
	
	//On vérifie les conditions de win
	this->_win = this->_enemy->getHP() <= 0;
	this->_loose = this->_eevee->getHP() <= 0 || this->_caught;
	this->_game->setBattle(!this->_win && !this->_loose && !this->_escape);

	if (!this->_game->getBattle()) {
		this->end();
		return 0;
	}
	else {
		return 1;
	}
}

void Battle::turn() {
	std::cout << "BATTLE TURN : " << this->_turn << std::endl;
	std::cout << "[Turn fonction] Choice : " << this->_choice << std::endl;
	//La fuite passe toujours en premier
	if (this->_choice == 2) {
		bool escape = this->random(2);

		if (escape) {
			this->interface->displayComment("You got away safely..", this->_win);
			this->_choice = 0;
			this->_enemy_choice = 0;
			this->_escape = true;
			return;
		}
		else {
			this->interface->displayComment("You couldn't get away !", this->_win);
		}
	}

	//Sélection de l'ennemi
	std::cout << "Calculating ennemy's choice..." << std::endl;

	//Au premier tour, on ne pourra pas se faire attraper
	if (this->_turn == 1) {
		this->_enemy_choice = this->random(2) + 1;
	}
	else {
		this->_enemy_choice = this->random(3) + 1;
	}

	//Debug only
	std::cout << "----------" << std::endl;
	std::cout << "Enemy choose " << this->_enemy_choice << std::endl;
	std::cout << "----------" << std::endl;

	//L'ennemi lancera toujours sa Pokeball avant notre attaque
	if (this->_enemy_choice == 3) {

		this->interface->displayComment("Enemy trow a pokeball !", this->_win);
		if (this->pokeball()) {
			this->interface->displayComment("You've been caught...", this->_win);
			this->_caught = true;
			return;
		}
		else {
			this->interface->displayComment("You escaped the pokeball !", this->_win);
		}
	}

	//S'il reste une action d'attaque à effectuer, on lance l'attaque
	if (this->_enemy_choice != 3 && this->_choice != 2) {
		//Si les deux doivent attaquer, on calcule l'initiative
		std::cout << "Calculating eevee's speed..." << std::endl;
		bool eevee = this->initiative();
		this->attack(eevee);
		if (this->battle()) {
			this->attack(!eevee);
		}
	}
	else if (this->_enemy_choice != 3 || this->_choice != 2) {
		if (this->_choice != 2) {
			this->attack(true);
		}
		else {
			this->attack(false);
		}
	}

	this->_choice = 0;
	this->_enemy_choice = 0;
	this->_turn++;
}

//
void Battle::attack(bool eevee) {
	//std::cout << "Attack function" << std::endl;
	int dodgerate;
	std::string name;

	if (this->_choice > 2 && !this->_eevee->isEvolved()) {
		this->_eevee->evolve(this->_choice);
		this->interface->displayComment("Eevee evolve to " + this->_eevee->getName(), this->_win);
		//Evolve
	}

	//On vérifie si c'est l'attaque de Eevee
	if (eevee) {
		//Si c'est le cas, on récupère la dodgerate de l'ennemi
		this->interface->displayComment("You attack !", this->_win);
		dodgerate = this->_enemy->getDodgerate();
	}
	else {
		//Sinon, celle d'Eevee
		this->interface->displayComment(this->_enemy->getName() + " attacks!", this->_win);
		dodgerate = this->_eevee->getDodgerate();
	}
		
	if (this->random(100) > dodgerate) {
	
		//Attack succeed
		//if special attack, bonus to dmg + different animation
		if (eevee) {
			//Si c'est Eevee qui attaque, on baisse les HP de l'ennemi
			this->_enemy->subHP(this->getDamage(true)); //temp dmg
			this->interface->displayComment("You attack !", this->_win);
		}
		else {
			//Sinon, c'est Eevee qui perds de la vie
			this->_eevee->subHP(this->getDamage(false));
			this->interface->displayComment(this->_enemy->getName() + " attacks!", this->_win);
			std::cout << this->_eevee->getHP();
			float percent = 20.0 / 100.0;

			if (this->_eevee->getHP() < percent * this->_eevee->getMaxHP()) {
				std::cout << "je suis low";
				this->music.setVolume(0);
				if (this->lowMusic.getStatus() != 2) {
					this->lowMusic.openFromFile("./sfx/Music/lowHp.wav");
					this->lowMusic.play();
				}
			}
		}
	}
	else {
		if (eevee) { //Si c'est Eevee qui attaque, c'est l'ennmi qui a dodge
			this->interface->displayComment(this->_enemy->getName() + " has dodged the attack !", this->_win);
		}
		else {
			this->interface->displayComment("You dodged the attack !", this->_win);
		}
	}
}

bool Battle::pokeball() {
	if (this->random(200) <= this->_eevee->catchrate()) {
		return true;
	}
	else {
		return false;
	}
}

bool Battle::initiative() {
	return this->_eevee->getSpeed() > this->_enemy->getSpeed();
}

int Battle::random(int range ) {
	srand(time(0));
	int random = rand() % range;
	return random;
}

int Battle::getDamage(bool eevee) {
	double damage;
	int attack, type1, type2;
	std::string name;

	if (eevee) { //Calcul des dégâts en fonction des stats de Eevee
		attack = this->_eevee->getAttack();
		std::cout << "Eevee Attack Stat : " << attack << std::endl;
		type1 = this->_eevee->getType();
		type2 = this->_enemy->getType();
		damage = 5;
		name = this->_enemy->getName();
	}
	else { //Sinon en fonction de celles de l'ennemi
		attack = this->_enemy->getAttack();
		std::cout << "Ennemy Attack Stat : " << attack << std::endl;
		type2 = this->_eevee->getType();
		damage = 2;
		name = this->_eevee->getName();

		if (this->_enemy_choice == 2) {
			type1 = this->_enemy->getType();
		}
		else {
			type1 = 1;
		}
	}

	damage = ((((((double)attack / 100) * 10) + damage) * this->checkType(type1, type2, name)));
	std::cout << "Damage dealt : " << damage << std::endl;
	return damage;
}

double Battle::checkType(int type1, int type2, std::string name) {
	sqlite3* db = getDatabase();
	createDatabase(db);
	//1[Name(100)] , 2[Effective], 3[Weakness], 4[Affect]
	std::cout << "Getting type datas..." << std::endl;
	std::vector<std::string> datas = getType(db, type1);

	std::vector<int> effective, weakness, affect;

	//for (size_t i = 0; i < datas.size(); i++)
	//{
	//	for (size_t j = 0; j < datas[i].size() ; j++)
	//	{
	//		if (i == 2 && isdigit(datas[i][j])) {
	//			int element = datas[i][j];
	//			effective.push_back(element);
	//			std::cout << effective[0] << std::endl;
	//			if (std::to_string(type2) == std::to_string(element)) {
	//				this->interface->displayComment("It's very effective !", this->_win);
	//				return 2; //Très efficace
	//			}
	//		}
	//		else if (i == 3 && isdigit(datas[i][j])) {
	//			//weakness.push_back(datas[i][j]);
	//			if (type2 == datas[i][j]) {
	//				this->interface->displayComment("It's not very effective...", this->_win);
	//				return 0.5; //Pas très efficace
	//			}
	//		}
	//		else if (i == 4 && isdigit(datas[i][j])) {
	//			//affect.push_back(datas[i][j]);
	//			if (type2 == datas[i][j]) {
	//				this->interface->displayComment("It doesn't affect " + name, this->_win);
	//				return 0; //N'affecte pas
	//			}
	//		}
	//	}
	//}

	/*return 1;*/ //Efficace

	if (stoi(datas[2]) == type2) { //Très efficace
		this->interface->displayComment("It's very effective !", this->_win);
		return 2;
	}
	else if (stoi(datas[3]) == type2) { //Pas très efficace
		this->interface->displayComment("It's not very effective...", this->_win);
		return 0.5;
	}
	else if (stoi(datas[4]) == type2) { //N'affecte pas
		this->interface->displayComment("It doesn't affect " + name, this->_win);
		return 0;
	}
	else { //Efficace
		return 1;
	}
}

//Setters

void Battle::setChoice(int choice) {
	std::cout << "i choose";
	this->_choice = choice;
}

//Getters

bool Battle::getChoice() { return this->_choice; }
bool Battle::getWin() { return this->_win; }

