#include "Battle.h"

Battle::Battle(Game* game, Eevee* eevee, Enemy* enemy) : _thread(&Battle::turn, this) {
	this->_eevee = eevee;
	this->_enemy = enemy;
	this->_game = game;
	this->music.openFromFile(musicTab[this->random(4)]);
	/*this->music.openFromFile("./sfx/Music/strongBattle.wav");*/
	this->music.setLoop(true);
	this->music.setVolume(10);
	this->reset();
}

Battle::~Battle() {};

void Battle::reset() {
	this->_win = this->_loose = this->_escape = false;
	this->_choice = this->_choosen_attack = this->_enemy_choice = 0;
	this->_turn = 1;

	this->_enemy->setHP(1); //temp
}

void Battle::end() {
	std::cout << "BATTLE ENDED" << std::endl;
	std::cout << "----------" << std::endl << std::endl;
	if (this->_win) {
		std::cout << "You win !!" << std::endl;
		this->loot();
	}
	else if (this->_loose) {
		std::cout << "You loose..." << std::endl;
		//écran game over
	}

	this->_eevee->setCoords(0, 30, 27, 3);
	this->reset();
}

void Battle::loot() {
	int loot = this->random(6);
	std::cout << "Getting loot : " << loot << std::endl;

	if (loot > 3) {
		this->_eevee->addLoot(loot);
	}
}

bool Battle::battle() {
	//Music
	//std::cout << this->music.getStatus() << std::endl;
	if (this->music.getStatus() != 2) {
		this->music.play();
	}
	//std::cout << "You encountered a wild " << this->_enemy->getName() << " !" << std::endl;

	//On vérifie les conditions de win
	this->_win = this->_enemy->getHP() <= 0;
	this->_loose = this->_eevee->getHP() <= 0;
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
			std::cout << "You got away safely !" << std::endl;
			this->_escape = true;
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
	std::cout << "----------" << std::endl;
	std::cout << "Enemy choose " << this->_enemy_choice << std::endl;
	std::cout << "----------" << std::endl;

	//L'ennemi lancera toujours sa Pokeball avant notre attaque
	if (this->_enemy_choice == 3) {
		std::cout << "Enemy trow a pokeball !" << std::endl;
		if (this->pokeball()) {
			std::cout << "You've been caught..." << std::endl;
			this->_loose = true;
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
		if (this->battle()) {
			this->attack(!eevee);
		}
	}
	else if (this->_enemy_choice != 3 || this->_choice == 1) {
		if (this->_choice == 1) {
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
		if (eevee) {
			this->_enemy->subHP(10); //temp dmg
		}
		else {
			this->_eevee->subHP(10);
		}
	}
	else {
		std::cout << name << " has dodged the attack !" << std::endl;
		//name has dodge the attack !
	}
}

bool Battle::pokeball() {
	if (this->random(100) <= this->_eevee->getCatchrate()) {
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

//Setters

void Battle::setChoice(int choice) {
	this->_choice = choice;
}

//Getters

bool Battle::getChoice() {
	return this->_choice;
}