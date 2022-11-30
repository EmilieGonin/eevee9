#include "Collision.h"

Collision::Collision(sf::RectangleShape &rectangle, bool wall, bool grass) : tile(rectangle){

	this->wall = wall;
	this->grass = grass;
}

sf::RectangleShape& Collision::gettile() { return this->tile; };


bool Collision::getcollision(Eevee* player) {
	sf::FloatRect bounds = this->tile.getGlobalBounds();
	sf::Sprite sprite = player->getSprite(2, 2);
	sf::FloatRect Eeveebounds = sprite.getGlobalBounds();
	if (this->wall) {
		/*std::cout << "x : " << this->tile.getPosition().x << " y : " << this->tile.getPosition().y << std::endl;
		std::cout << "eevee" << std::endl;
		std::cout << "x : " << sprite.getPosition().x << " y : " << sprite.getPosition().y << std::endl;*/
		if (bounds.intersects(Eeveebounds)) {
			/*std::cout << "TRUE" << std::endl;*/
			return 1;
		}
	}
	else if (this->grass) {
		if (bounds.contains(sprite.getPosition())) {
			return 1;
		}
	}
	return 0;
}