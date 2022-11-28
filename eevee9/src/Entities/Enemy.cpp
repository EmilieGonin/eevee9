#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture) : AnimatedEntity(texture) {
	this->name = "(name)"; //database
	this->speed = 0; //database
	this->sprite.scale(1, 1);
}
Enemy::~Enemy() {}
