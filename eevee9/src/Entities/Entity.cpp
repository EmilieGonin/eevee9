#include "Entity.h"

Entity::Entity(const sf::Texture& texture) : sprite(texture), texture(texture)
{
    this->dodgerate = 0;
    this->speed = 0;
    this->hp = 1;
    this->orientation = DOWN;
    this->y = 0;
    this->xSize = 132.5;
    this->ySize = 132.5;
    this->spriteFrames = 4;
}

//Setters

void Entity::subHP(int dmg) {
    this->hp = this->hp - dmg;
}

void Entity::setOrientation(int orientation)
{
    this->orientation = orientation;
}

//Getters

sf::Sprite Entity::getSprite()
{
    return this->sprite;
}

int Entity::getHP() {
    return this->hp;
}

int Entity::getOrientation() 
{
    return this->orientation;
}

int Entity::getDodgerate() {
	return  this->dodgerate;
}

int Entity::getSpeed() {
    return this->speed;
}

std::string Entity::getName() {
    return this->name;
}