#include "Eevee.h"


Eevee::Eevee(sf::Texture &texture) : AnimatedEntity(texture) {
	//Entity datas
	this->name = "Eevee"; // le joueur peut modifier ?
	this->hp = 55;
	this->maxHp = 55;
	this->speed = 55;
	this->orientation = DOWN;

	//Sprite
	this->xSize = 30;
	this->ySize = 28;
	this->spriteFrames = 3;

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

void Eevee::evolve(int eeveelution) {
	this->eeveelution = eeveelution;

	int frame = 0;

	if (eeveelution == 1) { //Vaporeon
		frame = 54;
	}
	else if (eeveelution == 2) { //Jolteon
		frame = 50;
	}
	else if (eeveelution == 3) { //Flareon
		frame = 84;
	}

	this->spriteFrames = frame;
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

void Eevee::collisionNotMoving(bool collision) {
	if(collision)
	{
		if (this->orientation == UP)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y + 5);
		}
		else if (this->orientation == DOWN)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 5);
		}
		else if (this->orientation == RIGHT)
		{
			this->sprite.setPosition(this->sprite.getPosition().x - 5, this->sprite.getPosition().y);
		}
		else if (this->orientation == LEFT)
		{
			this->sprite.setPosition(this->sprite.getPosition().x + 5, this->sprite.getPosition().y);
		}
	}
}
void Eevee::move(bool collision) {

	int changeX = 0;
	int changeY = 0;

	if (this->orientation == DOWN) {
		changeY = 2; 
	}
	if (this->orientation == UP) {
		 changeY = -2; 
	}
		
	if (this->orientation == RIGHT) {
		 changeX = 2; 
		}
	if (this->orientation == LEFT) {
		 changeX = -2; 
		}
	std::cout << this->orientation << std::endl;

	if (!collision) {
		this->sprite.move(changeX * PAS, changeY * PAS);
	}
	else {
		if (this->orientation == UP)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y + 1);
		}
		else if (this->orientation == DOWN)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 1);
		}
		else if (this->orientation == RIGHT)
		{
			this->sprite.setPosition(this->sprite.getPosition().x - 1, this->sprite.getPosition().y);
		}
		else if (this->orientation == LEFT)
		{
			this->sprite.setPosition(this->sprite.getPosition().x + 1, this->sprite.getPosition().y);
		}
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
