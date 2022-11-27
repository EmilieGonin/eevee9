#include "Eevee.h"
#include <iostream>


Eevee::Eevee(sf::Texture &texture) : AnimatedEntity(texture) {
	//Entity datas
	this->name = "Eevee"; // le joueur peut modifier ?
	this->hp = 55;
	this->speed = 55;
	this->sprite.scale(1, 1);
	this->orientation = DOWN;

	//Eevee datas
	this->catchrate = 6;

	//Evolution
	this->eeveelution = 0;
	this->evolved = false;

	//Stones
	this->firestone = 0;
	this->waterstone = 0;
	this->thunderstone = 0;
};

Eevee::~Eevee() {};

void Eevee::evolve() {
	//
}

bool Eevee::canEvolve() {
	if (this->firestone > 0 || this->waterstone > 0 || this->thunderstone > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Eevee::addLoot(int loot) {
	if (loot == 1) {
		this->firestone++;
	}
	else if (loot == 2) {
		this->waterstone++;
	}
	else if (loot == 3) {
		this->thunderstone++;
	}
}

bool Eevee::escape() {
	//
	int random = 0;
	return true;
}

void Eevee::move() {

	int changeX = 0;
	int changeY = 0;

	if (this->orientation == DOWN) {
		changeY = 1;
	}
	else if (this->orientation == UP) {
		changeY = -1;
	}
	else if (this->orientation == RIGHT) {
		changeX = 1;
	}
	else if (this->orientation == LEFT) {
		changeX = -1;
	}

	this->sprite.move(changeX * PAS, changeY * PAS);
}

//Getters

int Eevee::getEeveelution() {
	return this->eeveelution;
}

bool Eevee::isEvolved() {
	return this->evolved;
}
