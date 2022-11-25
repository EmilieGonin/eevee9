#include "Battle.h"
#include <random>
#include <iostream>

Battle::Battle(Eevee* eevee, Enemy* enemy) {
	std::cout << "Battle initiated !" << std::endl;
	this->_eevee = eevee;
	this->_enemy = enemy;
	this->_fighting = true;
	this->_win = false;
	this->_loose = false;
	this->_choice = 0;
	this->_turn = 1; //random ? initiative ?

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
		this->turn();
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
	if (this->_turn) {
		while (this->_choice == 0) {
			std::cout << "Choose an action !" << std::endl;
			std::cin >> this->_choice;
			//afficher menu

			//1 == Attack
			if (this->_choice == 1) {
				std::cout << "You attack !" << std::endl;
				this->attack(0);
			}
			//2 == Escape ?
			else if (this->_choice == 2) {
				std::cout << "You escaped the fight !" << std::endl;
				this->_fighting = false;
			}

			this->_turn = false;
		}
	}
	else {
		std::cout << "Enemy's turn" << std::endl;
		int choice = this->random(3) + 1;
		//Attack, special attack or catch

		if (choice == 1) {
			std::cout << "Enemy attack !" << std::endl;
			this->attack(0);
		}
		else if (choice == 2) {
			std::cout << "Enemy use its special attack !" << std::endl;
			this->attack(1);
		}
		else if (choice == 3) {
			std::cout << "Enemy trow a pokeball !" << std::endl;
			this->pokeball();
		}

		this->_turn = true;
	}
}

//0 = normal attack, 1 = Special attack
void Battle::attack(bool special) {
	std::cout << "Attack function" << std::endl;
	int dodgerate;
	std::string name;

	if (this->_turn) {
		dodgerate = this->_eevee->getDodgerate();
		name = this->_eevee->getName();
	}
	else {
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

void Battle::pokeball() {
	//
}

int Battle::random(int range ) {
	srand(time(0));
	int random = rand() % range;
	return random;
}