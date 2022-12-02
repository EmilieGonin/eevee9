#include "Entity.h"

Entity::Entity(const sf::Texture& texture, sqlite3* db) : sprite(texture), texture(texture), db(db) {
    this->hp = this->maxHp = this->attack = this->speed = this->dodgerate = this->type = 1;
    this->orientation = DOWN;
    this->y = this->spriteFrames = 0;
    this->xSize = this->ySize = 96;
}

//Setters

void Entity::subHP(int dmg) {
    this->hp = this->hp - dmg;
    if (this->hp < 0) {
        this->hp = 0;
    }
}
void Entity::setHP(int hp) { this->hp = hp; }
void Entity::setOrientation(int orientation) { this->orientation = orientation; }
void Entity::setY(int y) { this->y = y; }
void Entity::setSpriteFrames(int frame) { this->spriteFrames = frame; }
void Entity::spritePosition(float x, float y) { this->sprite.setPosition(x, y); }
void Entity::setCoords(int y, int xSize, int ySize, int frames) {
    this->spriteFrames = frames;
    this->y = y;
    this->xSize = xSize;
    this->ySize = ySize;
}

//Getters

sf::Sprite Entity::getSprite(float x, float y) {
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
int Entity::getAttack() { return this->attack; }
int Entity::getType() { return this->type; }