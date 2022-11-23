#include "Eevee.h"

Eevee::Eevee() {
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