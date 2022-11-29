#include "Test.h"

Test::Test(float x, float y, bool wall) {
	sf::RectangleShape rectangle(sf::Vector2f(x, y));
	//rectangle.setPosition(10, 10);

	this->wall = wall;
	this->grass = true;
	this->x = rectangle.getPosition().x;
	this->y = rectangle.getPosition().y;
	//std::cout << this->tile->getPosition().x << std::endl;
}


bool Test::collision(Eevee* player) {
	//std::cout << "test" << std::endl;
	sf::Sprite sprite = player->getSprite();
	if (this->wall) {
		//std::cout << "this is a wall" << std::endl;
		//std::cout << "x : " << this->tile->getPosition().x << " y : " << this->tile->getPosition().y << std::endl;
		std::cout << this->x << std::endl;
		std::cout << "eevee" << std::endl;
		std::cout << "x : " << sprite.getPosition().x << " y : " << sprite.getPosition().y << std::endl;
		if (sprite.getPosition().x - 2 == this->x) {
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