#include "Eevee.h"

#include <iostream>

Eevee::Eevee(sf::Texture &texture) : AnimatedEntity(texture) {
	this->hp = 55;
	this->catchrate = 6;
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


sf::Sprite Eevee::getSprite()
{
    return this-> sprite;
}


