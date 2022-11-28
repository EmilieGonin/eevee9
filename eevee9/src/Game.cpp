#include "Game.h"
#include <iostream>

Game::Game()
{
    window = new sf::RenderWindow();
    window->create(sf::VideoMode(992, 672), "Menu SFML", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);
    this->pause = false;
    this->keypressed = NULL;
}

Game::~Game() {};


void Game::draw(Entity& entity) { window->draw(entity.getSprite()); };

int Game::update(int orientation) {
    int newOrientation = orientation;
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window->close();
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
                else if (event.key.code == sf::Keyboard::Escape) {
                    std::cout << "run pause menu" << std::endl;
                    this->pause = true;
                    //runMenu();

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


void Game::clear() { window->clear(); };
void Game::display() { window->display(); };

bool Game::isOpen() {
    return window->isOpen();
}

bool Game::isMoving() {
    if (this->keypressed) {
        return true;
    }
    else {
        return false;
    }
}

int Game::getKeyPressed() {
    return this->keypressed;
}

bool Game::getPause() { return this->pause; }

sf::RenderWindow& Game::getWindow() { return *this->window; }

void Game::setPause(bool pause) {
    this->pause = pause;
}