#pragma once
class Battle
{
protected:
	bool win;
	bool loose;
	int choice;
public:
	void loot(); // Choose a random loot on a scale of 0 to 6, 0-3 = nothing
};

