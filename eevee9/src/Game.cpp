#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Epic 9")
{
	this->window.setFramerateLimit(60);
    this->keypressed = NULL;
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
            if (!this->keypressed) {
                if (event.key.code == sf::Keyboard::Z) {
                    newOrientation = UP;
                    this->keypressed = sf::Keyboard::Z;
                }
                else if (event.key.code == sf::Keyboard::D) {
                    newOrientation = RIGHT;
                    this->keypressed = sf::Keyboard::D;
                }
                else if (event.key.code == sf::Keyboard::S) {
                    newOrientation = DOWN;
                    this->keypressed = sf::Keyboard::S;
                }
                else if (event.key.code == sf::Keyboard::Q) {
                    newOrientation = LEFT;
                    this->keypressed = sf::Keyboard::Q;
                }
            }
            break;
        case sf::Event::KeyReleased:
            if (event.key.code == this->keypressed)
            this->keypressed = NULL;
          
        }
    };
    return newOrientation;
}
void Game::clear() { this->window.clear(); };
void Game::display() { this->window.display(); };

bool Game::isOpen() {
    return this->window.isOpen();
}

bool Game::isMoving() {
    if (this->keypressed) {
        return true;
    }
    else {
        return false;
    }
}