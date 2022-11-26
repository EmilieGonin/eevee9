#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Utils.h"
#include "Entity.h"


class Game
{
protected:
	
	int keypressed;
	sf::RenderWindow *window;

public:
	Game();
	~Game();
	void draw(Entity &);
	void clear();
	void display();
	int update(int);
	bool isOpen();
	bool isMoving();

	int getKeyPressed();

};

