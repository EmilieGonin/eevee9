#include "Entity.h"

Entity::Entity(const sf::Texture& texture) : sprite(texture), texture(texture)
{
    this->dodgerate = 0;
    this->speed = 0;
    this->hp = 1;
    this->orientation = DOWN;
    this->y = 0;
    this->xSize = 30;
    this->ySize = 27;
    this->spriteFrames = 3;
}

//Setters

void Entity::setHP(int hp) {
    this->hp = hp;
}

void Entity::subHP(int dmg) {
    this->hp = this->hp - dmg;
}

void Entity::setOrientation(int orientation)
{
    this->orientation = orientation;
}

void Entity::setCoords(int y, int xSize, int ySize, int frames) {
    this->spriteFrames = frames;
    this->y = y;
    this->xSize = xSize;
    this->ySize = ySize;
}

void Entity::spritePosition(float x, float y) {
    this->sprite.setPosition(x, y);

}

//Getters

sf::Sprite Entity::getSprite(float x, float y)
{
    this->sprite.setScale(x, y);
    return this->sprite;
}

int Entity::getHP() { return this->hp; }
int Entity::getOrientation() { return this->orientation; }
int Entity::getDodgerate() { return  this->dodgerate; }
int Entity::getSpeed() { return this->speed; }
std::string Entity::getName() { return this->name; }