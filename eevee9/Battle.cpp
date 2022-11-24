#include "Battle.h"
#include <random>
#include <iostream>

Battle::Battle(Eevee* eevee, Enemy* enemy) {
	this->_eevee = eevee;
	this->_enemy = enemy;
	this->_win = false;
	this->_loose = false;
	this->_choice = 0;
	this->_turn = 1; //random ? initiative ?
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
	while (!this->_win || !this->_loose) {
		this->turn();
	}

	if (this->_win) {
		this->loot();
	}
	else {
		//écran game over
	}
}

void Battle::turn() {
	if (this->_turn) {
		while (this->_choice == 0) {
			//afficher menu
		}
	}
	else {
		//Attack or catch
		this->attack();
	}
}

void Battle::attack() {
	int dodgerate;
	if (this->_turn) {
		dodgerate = this->_eevee->getDodgerate();
	}
	else {
		dodgerate = this->_enemy->getDodgerate();
	}

	if (this->_turn) {
		if (this->random() > dodgerate) {
			//
		}
		else {
			//Eevee dodge
		}
	}
	else {
		//
	}
}

int Battle::random(int range = 100) {
	srand(time(NULL));
	int random = rand() % range;
	return random;
}