#pragma once

#include "Entity.h"


class Game
{
protected:
	bool pause, battle;

	int keypressed;
	sf::RenderWindow *window;

public:
	Game();
	~Game();

	//Window & Sprite
	void draw(Entity &);
	void clear();
	void display();
	bool isOpen();
	bool isMoving();
	int update(int);

	//Setters
	void setPause(bool);

	//Getters
	bool getPause();
	bool getBattle();
	int getKeyPressed();
	sf::RenderWindow* getWindow();

};

