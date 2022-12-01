#pragma once

#include "Eevee.h"
#include "Enemy.h"
#include "Game.h"
#include "Interface.h"

class Battle
{
protected:
	bool _win, _loose, _escape, _positionSaved;
	int _choice; //1 = Attack, 2 = Escape
	int _choosen_attack; //Attaque de Eevee si choisie
	int _enemy_choice; //1 = Attack, 2 = Special Attack, 3 = Pokeball
	int _turn; //Number of turn
	Eevee* _eevee;
	Enemy* _enemy;
	Game* _game;
	Interface* interface;
	sf::Music music;
	sf::Music lowMusic;
	std::string musicTab[4] = { "./sfx/Music/battle.wav" , "./sfx/Music/battle2.wav" , "./sfx/Music/battle3.wav" , "./sfx/Music/battle4.wav" };
	std::string whatHappened;

public:
	Battle(Game*, Eevee*, Enemy*, Interface*);
	~Battle();
	void reset();
	void end();
	void loot(); // Choose a random loot on a scale of 0 to 6, 0-3 = nothing
	bool battle();
	void turn();
	void attack(bool);
	bool pokeball();
	bool initiative(); // If Eevee is faster than the enemy
	int random(int);

	//Setters
	void setChoice(int);

	//Getters
	bool getChoice();
	bool getWin();
};

