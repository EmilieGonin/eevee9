#pragma once
#include "Eevee.h"
#include "Enemy.h"

class Battle
{
protected:
	bool _win;
	bool _loose;
	int _choice;
	Eevee* _eevee;
	Enemy* _enemy;
public:
	Battle(Eevee*, Enemy*);
	~Battle();
	void loot(); // Choose a random loot on a scale of 0 to 6, 0-3 = nothing
	void turn();
};

