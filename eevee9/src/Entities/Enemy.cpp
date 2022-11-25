#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture) : AnimatedEntity(texture) {
	this->name = "UC"; //database
	this->sprite.scale(1, 1);
}
Enemy::~Enemy() {}
