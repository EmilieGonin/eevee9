#include "Game.h"

Game::Game()
{
    window = new sf::RenderWindow();
    window->create(sf::VideoMode(992, 672), "Pokemon: Eevee 9", sf::Style::Titlebar | sf::Style::Close);
    this->pause = false;
    this->battle = false;
    this->keypressed = NULL;
}

Game::~Game() {};

//Window & Sprite

void Game::draw(Entity& entity) { window->draw(entity.getSprite()); };
void Game::clear() { window->clear(); };
void Game::display() { window->display(); };
bool Game::isOpen() { return window->isOpen(); }

bool Game::isMoving() {
    if (this->keypressed) {
        return true;
    }
    else {
        return false;
    }
}

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
            if (!this->keypressed && this->pause == false) {
                if (event.key.code == sf::Keyboard::Z ||
                    event.key.code == sf::Keyboard::Up) {
                    newOrientation = UP;
                    this->keypressed = event.key.code;
                }
                else if (event.key.code == sf::Keyboard::D ||
                    event.key.code == sf::Keyboard::Right) {
                    newOrientation = RIGHT;
                    this->keypressed = event.key.code;
                }
                else if (event.key.code == sf::Keyboard::S ||
                    event.key.code == sf::Keyboard::Down) {
                    newOrientation = DOWN;
                    this->keypressed = event.key.code;
                }
                else if (event.key.code == sf::Keyboard::Q ||
                    event.key.code == sf::Keyboard::Left) {
                    newOrientation = LEFT;
                    this->keypressed = event.key.code;
                }
                else if (event.key.code == sf::Keyboard::Escape) {
                    std::cout << "run pause menu" << std::endl;
                    this->pause = true;
                }
                else if (event.key.code == sf::Keyboard::B) {
                    this->battle = true;
                    std::cout << "Battle START" << std::endl;
                    std::cout << "----------" << std::endl;
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

//Setters

void Game::setPause(bool pause) {
    this->pause = pause;
}

void Game::setBattle(bool battle) {
    this->battle = battle;
}

//Getters

bool Game::getBattle() { return this->battle; }
bool Game::getPause() { return this->pause; }
int Game::getKeyPressed() { return this->keypressed; }
sf::RenderWindow* Game::getWindow() { return this->window; }