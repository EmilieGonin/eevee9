#include "Eevee.h"


Eevee::Eevee(sf::Texture &texture) : AnimatedEntity(texture) {
	//Entity datas
	this->name = "Eevee"; // le joueur peut modifier ?
	this->hp = 55;
	this->maxHp = 55;
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
	//Change this->y;
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

void Eevee::move(bool collision) {

	int changeX = 0;
	int changeY = 0;

	if (this->orientation == DOWN) {
		if (!collision) { changeY = 2; }
	}
	else if (this->orientation == UP) {
		if (!collision) { changeY = -2; }
	}
		
		else if (this->orientation == RIGHT) {
			if (!collision) { changeX = 2; }
		}
		else if (this->orientation == LEFT) {
			if (!collision) { changeX = -2; }
		}
	std::cout << this->orientation << std::endl;

	if (!collision) {
		this->sprite.move(changeX * PAS, changeY * PAS);
	}
	else {
		this->sprite.setPosition(this->sprite.getPosition().x , this->sprite.getPosition().y +1);
	}
		
	
	
}

//Getters

int Eevee::getCatchrate() {
	return this->catchrate;
}

int Eevee::getEeveelution() {
	return this->eeveelution;
}

bool Eevee::isEvolved() {
	return this->evolved;
}
