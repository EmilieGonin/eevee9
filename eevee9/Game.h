#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Utils.h"
class Game
{
	protected:
			
		sf::RenderWindow window;
	public:

		Game();
		~Game();
		void draw(sf::Sprite objectToDraw);
		void clear();
		void display();
		int update(int actualOrientation);
		bool isOpen();

};

