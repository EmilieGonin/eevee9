#include "Entity.h"

Entity::Entity(const sf::Texture& texture, sqlite3* db) : sprite(texture), texture(texture), db(db)
{
    this->hp = 70;
    this->maxHp = 1;
    this->orientation = DOWN;
    this->dodgerate = this->speed = this->y = this->spriteFrames = 0;
    this->xSize = this->ySize = 96;
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

void Entity::setY(int y) {
    this->y = y;
}

void Entity::setSpriteFrames(int frame) {
    this->spriteFrames = frame;
}

//Getters

sf::Sprite Entity::getSprite(float x, float y)
{
    this->sprite.setScale(x, y);
    return this->sprite;
}

int Entity::getHP() { return this->hp; }
int Entity::getMaxHP() { return this->maxHp; }
int Entity::getOrientation() { return this->orientation; }
int Entity::getDodgerate() { return  this->dodgerate; }
int Entity::getSpeed() { return this->speed; }
std::string Entity::getName() { return this->name; }
int Entity::getY() { return this->y; }
int Entity::getSpriteFrames() { return this->spriteFrames; }