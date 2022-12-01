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
	std::vector<std::vector<sf::RectangleShape>*> map1;
	std::vector<std::vector<sf::RectangleShape>*> map2;
	std::vector<sf::RectangleShape> walls;
	std::vector<sf::RectangleShape> grass;
	std::vector<sf::RectangleShape> tp;

	void randomBattle(bool);

	//Setters
	void setPause(bool);
	void setBattle(bool);

	//Getters
	bool getPause();
	bool getBattle();
	int getKeyPressed();
	sf::RenderWindow* getWindow();
	void CreateShapes(int);
	bool CreateCollision(Eevee*);
	bool sethovergrass(Eevee*);
	bool setHoverTp(Eevee*);

};

