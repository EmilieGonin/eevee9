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

void Game::draw(Entity& entity) { window->draw(entity.getSprite(2,2)); };
void Game::drawtile() { 
    for (size_t i = 0; i < this->walls.size(); i++)
    {
        window->draw(this->walls[i]);
    }

    for (size_t i = 0; i < this->grass.size(); i++)
    {
        window->draw(this->grass[i]);
    }

};

bool Game::CreateCollision(Eevee* player) {
    for (size_t i = 0; i < this->walls.size(); i++)
    {
        Collision col(walls[i], true, false);
        if (col.getcollision(player)) {
            return true;
        }
    }
    
    return false;

};

bool Game::sethovergrass(Eevee* player) {
    for (size_t i = 0; i < this->grass.size(); i++)
    {
        Collision col(grass[i], false, true);
        if (col.getcollision(player)) {
            std::cout << "True" << std::endl;
            return true;
        }
    }
    return false;
};


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
                    std::cout << "----------" << std::endl;
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

void Game::CreateShapes() {


    sf::RectangleShape wall1(sf::Vector2f(992, 75));
    wall1.setPosition(0, 0);
    wall1.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall1);

    sf::RectangleShape wall2(sf::Vector2f(75, 480));
    wall2.setPosition(940, 0);
    wall2.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall2);

    sf::RectangleShape wall3(sf::Vector2f(75, 100));
    wall3.setPosition(940, 585);
    wall3.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall3);

    sf::RectangleShape wall4(sf::Vector2f(992, 32));
    wall4.setPosition(0, 650);
    wall4.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall4);

    sf::RectangleShape wall5(sf::Vector2f(180, 240));
    wall5.setPosition(0, 0);
    wall5.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall5);

    sf::RectangleShape wall6(sf::Vector2f(242, 190));
    wall6.setPosition(0, 237);
    wall6.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall6);

    sf::RectangleShape wall7(sf::Vector2f(175, 175));
    wall7.setPosition(0, 412);
    wall7.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall7);

    sf::RectangleShape wall8(sf::Vector2f(1, 100));
    wall8.setPosition(250, 530);
    wall8.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall8);

    sf::RectangleShape wall9(sf::Vector2f(125, 88));
    wall9.setPosition(500, 394);
    wall9.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall9);

    sf::RectangleShape wall10(sf::Vector2f(1, 110));
    wall10.setPosition(342, 430);
    wall10.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall10);

    sf::RectangleShape wall11(sf::Vector2f(80, 1));
    wall11.setPosition(242, 426);
    wall11.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall11);

    sf::RectangleShape wall12(sf::Vector2f(45, 5));
    wall12.setPosition(860, 432);
    wall12.setFillColor(sf::Color::Transparent);
    this->walls.push_back(wall12);

    sf::RectangleShape grass(sf::Vector2f(620, 90));
    grass.setPosition(293, 96);
    grass.setFillColor(sf::Color::Yellow);
    this->grass.push_back(grass);

    sf::RectangleShape grass2(sf::Vector2f(305, 56));
    grass2.setPosition(618, 192);
    grass2.setFillColor(sf::Color::Yellow);
    this->grass.push_back(grass2);

    sf::RectangleShape grass3(sf::Vector2f(84, 150));
    grass3.setPosition(842, 256);
    grass3.setFillColor(sf::Color::Yellow);
    this->grass.push_back(grass3);

    sf::RectangleShape grass4(sf::Vector2f(50, 200));
    grass4.setPosition(262, 200);
    grass4.setFillColor(sf::Color::Yellow);
    this->grass.push_back(grass4);

}

//Getters

bool Game::getBattle() { return this->battle; }
bool Game::getPause() { return this->pause; }
int Game::getKeyPressed() { return this->keypressed; }
sf::RenderWindow* Game::getWindow() { return this->window; }