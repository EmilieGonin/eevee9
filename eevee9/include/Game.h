#pragma once

#include "Entity.h"
#include "Collision.h"
#include "CollisionNPC.h"
#include "SpriteMap.h"

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
	std::vector<std::vector<sf::RectangleShape>*> map3;

	std::vector<std::vector<sf::Sprite>*> sprites1;
	std::vector<std::vector<sf::Sprite>*> sprites2;
	std::vector<std::vector<sf::Sprite>*> sprites3;
	std::vector <sf::Sprite> sprites;

	std::vector<sf::RectangleShape> walls;
	std::vector<sf::RectangleShape> grass;
	std::vector<sf::RectangleShape> tp;
	std::vector<sf::RectangleShape> interact;
	

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
	bool setColSprites(Eevee*);
	bool setInteractShop(Eevee*);

};

