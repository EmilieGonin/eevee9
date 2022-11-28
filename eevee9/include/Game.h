#pragma once

#include "Entity.h"


class Game
{
protected:
	
	int keypressed;
	sf::RenderWindow *window;
	bool pause;

public:
	Game();
	~Game();
	void draw(Entity &);
	void clear();
	void display();
	int update(int);
	bool isOpen();
	bool isMoving();
	bool getPause();
	void setPause(bool);
	sf::RenderWindow* getWindow();
	int getKeyPressed();

};

