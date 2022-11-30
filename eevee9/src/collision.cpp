#include "Collision.h"

Collision::Collision(sf::RectangleShape& rectangle, bool wall, bool grass) : tile(rectangle) {

	this->wall = wall;
	this->grass = grass;
};

sf::RectangleShape& Collision::gettile() { return this->tile; };


bool Collision::getcollision(Eevee* player) {
	sf::FloatRect bounds = this->tile.getGlobalBounds();
	sf::Sprite sprite = player->getSprite(2, 2);
	sf::FloatRect Eeveebounds = sprite.getGlobalBounds();
	if (this->wall) {
		if (bounds.intersects(Eeveebounds)) {
			return 1;
		}
	}
	if (this->grass) {
		if (bounds.contains(sprite.getPosition())) {
			return 1;
		}
	}
	else { return 0; }
}
