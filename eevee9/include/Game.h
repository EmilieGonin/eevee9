#pragma once

#include "Entity.h"
#include "Collision.h"


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
	void drawtile();
	void clear();
	void display();
	bool isOpen();
	bool isMoving();
	int update(int);
	std::vector<sf::RectangleShape> walls;
	std::vector<sf::RectangleShape> grass;

	//Setters
	void setPause(bool);
	void setBattle(bool);

	//Getters
	bool getPause();
	bool getBattle();
	int getKeyPressed();
	sf::RenderWindow* getWindow();
	void CreateShapes();
	bool setCollision(Eevee*);

};

