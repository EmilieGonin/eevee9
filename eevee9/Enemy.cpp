#include "Enemy.h"

Enemy::Enemy() : AnimatedEntity(texture) {
	this->sprite.scale(1, 1);
}
Enemy::~Enemy() {}
