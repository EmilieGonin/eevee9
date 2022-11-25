#include "Entity.h"

Entity::Entity(const sf::Texture& texture) : sprite(texture), texture(texture)
{
    this->dodgerate = 0;
    this->hp = 0;
    this->orientation = DOWN;
}

//sf::Sprite& Entity::getSprite(void)
//{
//    return this->sprite;
//}

sf::Sprite Entity::getSprite()
{
    return this->sprite;
}

void Entity::setOrientation(int orientation) 
{
    this->orientation = orientation;
}

int Entity::getOrientation() 
{
    return this->orientation;
}

int Entity::getDodgerate() {
	return  this->dodgerate;
}

std::string Entity::getName() {
    return this->name;
}