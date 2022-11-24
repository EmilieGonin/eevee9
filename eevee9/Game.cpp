#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Epic 9")
{
	this->window.setFramerateLimit(60);
}

Game::~Game() {};

void Game::draw(Entity& entity) { this->window.draw(entity.getSprite()); };

int Game::update(int orientation) {
    int newOrientation = orientation;
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Z) {
                newOrientation =  UP;
    
            }
            else if (event.key.code == sf::Keyboard::D) {
                newOrientation = RIGHT;

            }
            else if (event.key.code == sf::Keyboard::S) {
                newOrientation = DOWN;

            }
            else if (event.key.code == sf::Keyboard::Q) {
                newOrientation = LEFT;

            }

            break;
        }
    };
    return newOrientation;
}
void Game::clear() { this->window.clear(); };
void Game::display() { this->window.display(); };

bool Game::isOpen() {
    return this->window.isOpen();
}
