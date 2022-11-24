#include "Battle.h"
#include <random>
#include <iostream>

Battle::Battle(Eevee* eevee, Enemy* enemy) {
	this->_eevee = eevee;
	this->_enemy = enemy;
	this->_win = false;
	this->_loose = false;
	this->_choice = 0;
}

Battle::~Battle() {};

void Battle::loot() {
	srand(time(NULL));
	int loot = rand() % 6;
	std::cout << "Getting loot : " << loot;

	if (loot > 3) {
		this->_eevee->addLoot(loot);
	}
}

void Battle::turn() {
	while (this->_choice == 0) {
		//afficher menu
	}
}