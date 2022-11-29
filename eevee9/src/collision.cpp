#include "Collision.h"

Collision::Collision(sf::RectangleShape &rectangle) : tile(rectangle) {

	this->wall = true;
	this->grass = true;
	/*this->tile = new sf::RectangleShape();
	this->tile->setSize(sf::Vector2f(x, y));
	this->tile->setPosition(z, a);
	this->tile->setFillColor(sf::Color::Red);*/
	//this->x = rectangle.getPosition().x;
	//this->y = rectangle.getPosition().y;
	//std::cout << this->tile->getPosition().x << std::endl;
}

sf::RectangleShape& Collision::gettile() { return this->tile; };

sf::RectangleShape Collision::tileGet() { return this->tile; };

bool Collision::getcollision(Eevee* player) {
	//std::cout << this->tile << std::endl;
	sf::FloatRect bounds = this->tile.getGlobalBounds();
	sf::Sprite sprite = player->getSprite(2,2);
	sf::FloatRect Eeveebounds = sprite.getGlobalBounds();
	if (this->wall) {
		//std::cout << "this is a wall" << std::endl;
		std::cout << "x : " << this->tile.getPosition().x << " y : " << this->tile.getPosition().y << std::endl;		
		std::cout << "eevee" << std::endl;
		std::cout << "x : " << sprite.getPosition().x << " y : " << sprite.getPosition().y << std::endl;
		if (bounds.intersects(Eeveebounds)) {
			std::cout << "TRUE" << std::endl;
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}