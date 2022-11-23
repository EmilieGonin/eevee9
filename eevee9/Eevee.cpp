#include "Eevee.h"
#include <iostream>

Eevee::Eevee() {};
Eevee::Eevee(sf::Texture texture) {
	this->hp = 55;
	this->catchrate = 6;
	this->firestone = 0;
	this->waterstone = 0;
	this->thunderstone = 0;

	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 132.5, 132.5));
	this->sprite.setScale(1, 1);
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

void Eevee::addStone(std::string stone) {
	if (stone == "fire") {
		this->firestone++;
	}
	else if (stone == "water") {
		this->waterstone++;
	}
	else if (stone == "thunder") {
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

    return this->sprite;
}

void Eevee::update()
{
    std::cout << this->count;
    if (this->count % 20 == 0)
    {
        this->iter = (this->iter + 1) % 4;
        std::cout << "oui";
        this->sprite.setTextureRect(sf::IntRect(this->iter * 132.5,132.5 * this->orientation,132.5,132.5));
        this->count = 0;
    }
    this->count++;
}

