#include "Battle.h"

Battle::Battle(Eevee* eevee, Enemy* enemy) {
	this->_eevee = eevee;
	this->_enemy = enemy;
	this->_fighting = true;
	this->_win = false;
	this->_loose = false;
	this->_choice = 0;
	this->_enemy_choice = 0;
	this->_turn = 1;

	std::cout << "You encountered a wild " << this->_enemy->getName() << " !" << std::endl;
	this->battle();
}

Battle::~Battle() {};

void Battle::loot() {
	int loot = this->random(6);
	std::cout << "Getting loot : " << loot;

	if (loot > 3) {
		this->_eevee->addLoot(loot);
	}
}

void Battle::battle() {
	while (this->_fighting) {
		this->_choice = 0;
		this->_enemy_choice = 0;
		this->turn();
		this->_turn++;
	}

	if (this->_win) {
		this->loot();
	}
	else if (this->_loose) {
		//écran game over
	}
}

void Battle::turn() {
	std::cout << "turn : " << this->_turn << std::endl;

	//Choix du joueur
	while (this->_choice == 0) {
		std::cout << "Choose an action !" << std::endl;
		std::cin >> this->_choice;
		//afficher menu
	}

	//La fuite passe toujours en premier
	if (this->_choice == 2) {
		bool escape = this->random(2);

		if (escape) {
			std::cout << "You got away safely !" << std::endl;
			this->_fighting = false;
			return;
		}
		else {
			std::cout << "You couldn't get away !" << std::endl;
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
	std::cout << "Enemy choose " << this->_enemy_choice << std::endl;

	//L'ennemi lancera toujours sa Pokeball avant notre attaque
	if (this->_enemy_choice == 3) {
		std::cout << "Enemy trow a pokeball !" << std::endl;
		if (this->pokeball()) {
			std::cout << "You've been caught..." << std::endl;
			this->_loose;
			return;
		}
		else {
			std::cout << "You escaped the pokeball !" << std::endl;
		}
	}

	//S'il reste une action d'attaque à effectuer, on lance l'attaque
	if (this->_enemy_choice != 3 && this->_choice != 2) {
		//Si les deux doivent attaquer, on calcule l'initiative
		std::cout << "Calculating eevee's speed..." << std::endl;
		bool eevee = this->initiative();
		this->attack(eevee);
		this->attack(!eevee);
	}
	else if (this->_enemy_choice != 3 || this->_choice == 1) {
		if (this->_choice == 1) {
			this->attack(true);
		}
		else {
			this->attack(false);
		}
	}
}

//
void Battle::attack(bool eevee) {
	std::cout << "Attack function" << std::endl;
	int dodgerate;
	std::string name;

	if (!this->_eevee->isEvolved() && this->_eevee->getEeveelution()) {
		std::cout << "Eevee evolve !" << std::endl;
		//Evolve
	}

	if (eevee) {
		std::cout << "You attack !" << std::endl;
		dodgerate = this->_eevee->getDodgerate();
		name = this->_eevee->getName();
	}
	else {
		if (this->_enemy_choice == 1) {
			std::cout << "Enemy attack !" << std::endl;
		}
		else {
			std::cout << "Enemy use its special attack !" << std::endl;
		}
		dodgerate = this->_enemy->getDodgerate();
		name = this->_enemy->getName();
	}

	if (this->random(100) > dodgerate) {
		std::cout << "Attack success !" << std::endl;
		//Attack succeed
		//if special attack, bonus to dmg + different animation
	}
	else {
		std::cout << "Attack dodged" << std::endl;
		//name has dodge the attack !
	}
}

bool Battle::pokeball() {
	return false;
}

bool Battle::initiative() {
	return this->_eevee->getSpeed() > this->_enemy->getSpeed();
}

int Battle::random(int range ) {
	srand(time(0));
	int random = rand() % range;
	return random;
}