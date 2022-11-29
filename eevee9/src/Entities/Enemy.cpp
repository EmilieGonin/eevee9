#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture) : AnimatedEntity(texture) {
	//
}
Enemy::~Enemy() {}


void Enemy::reset() {
	this->y = 0;
}

void Enemy::set() {
	this->name = "(name)"; //database
	this->speed = 0; //database
	this->xSize = this->ySize = 0;
	this->y = (0 - 1) * this->ySize; //On relie la rangée de texture par rapport à l'identifiant
}