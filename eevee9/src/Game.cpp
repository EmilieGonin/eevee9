#include "Game.h"

Game::Game() {
    window = new sf::RenderWindow();
    window->create(sf::VideoMode(992, 672), "Pokemon: Eevee 9", sf::Style::Titlebar | sf::Style::Close);
    this->pause = this->battle = false;
    this->keypressed = NULL;
}

Game::~Game() {};

//Window & Sprite

void Game::draw(Entity& entity) { window->draw(entity.getSprite(2,2)); };
void Game::drawtile() { 
    for (size_t i = 0; i < this->walls.size(); i++) {
        window->draw(this->walls[i]);
    }

    for (size_t i = 0; i < this->grass.size(); i++) {
        window->draw(this->grass[i]);
    }

    for (size_t i = 0; i < this->tp.size(); i++) {
        window->draw(this->tp[i]);
    }

    for (size_t i = 0; i < this->interact.size(); i++)
    {
        window->draw(this->interact[i]);
    }
    for (size_t i = 0; i < this->sprites.size(); i++)
    {
        window->draw(this->sprites[i]);

    }
    for (size_t i = 0; i < this->interactitem.size(); i++)
    {
        window->draw(this->interactitem[i]);

    }
};

bool Game::CreateCollision(Eevee* player) {
    for (size_t i = 0; i < this->walls.size(); i++) {
        Collision col(walls[i]);
        if (col.getcollision(player)) {
            std::cout << "wall";
            return true;
        }
    }
    return false;

};

bool Game::sethovergrass(Eevee* player) {
    for (size_t i = 0; i < this->grass.size(); i++)
    {
        Collision grasss(grass[i]);
        if (grasss.getcollision(player)) {
            std::cout << "grass";
            return true;
        }
    }
    return false;
};

bool Game::setHoverTp(Eevee* player) {
    for (size_t i = 0; i < this->tp.size(); i++)
    {
        Collision tpp(tp[i]);
        if (tpp.getcollision(player)) {
            std::cout << "tp";
            return true;
        }
    }
    return false;
};


bool Game::setColSprites(Eevee* player) {
    for (size_t i = 0; i < this->sprites.size(); i++)
    {
        CollisionNPC sprite(sprites[i]);
        if (sprite.getcollision(player)) {

            return true;
        }
    }
    return false;
};

bool Game::setInteractShop(Eevee* player) {
    for (size_t i = 0; i < this->interact.size(); i++)
    {
        Collision shop(interact[i]);
        if (shop.getcollision(player)) {

            return true;
        }
    }
    return false;
};

bool Game::setInteractItem(Eevee* player) {
    for (size_t i = 0; i < this->interactitem.size(); i++)
    {
        Collision item(interactitem[i]);
        if (item.getcollision(player)) {
            sqlite3* db = getDatabase();
            //removeItem(db, item.gettile().getPosition().x, item.gettile().getPosition().y);
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

    while (window->pollEvent(event)) {
        switch (event.type) {
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

void Game::setPause(bool pause) { this->pause = pause; }
void Game::setBattle(bool battle) { this->battle = battle; }
void Game::randomBattle(bool grass) {
    int random = rand() % 100;  
    if (random < 2 && grass) {
        setBattle(true);
        this->keypressed = NULL;
    }
    else
    {
        setBattle(false);
    }
}

void Game::CreateShapes(int mapId) {
    

    

    if(mapId == 0 ) {
        while(this->map2.size() != 0) {
            for (size_t i = 0; i < this->map2.size(); i++) {
                std::cout << "je delete";
                while (this->map2[i]->size() != 0) {
                    this->map2[i]->pop_back();
                };
            }
            this->map2.pop_back();
        }



        if (this->map1.size() == 0) {
       
            sf::Texture* itemTexture = new sf::Texture();
            itemTexture->loadFromFile("./img/item.png");

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

            sf::RectangleShape grass(sf::Vector2f(600, 55));
            grass.setPosition(310, 96);
            grass.setFillColor(sf::Color::Transparent);
            this->grass.push_back(grass);

            sf::RectangleShape grass2(sf::Vector2f(280, 25));
            grass2.setPosition(640, 192);
            grass2.setFillColor(sf::Color::Transparent);
            this->grass.push_back(grass2);

            sf::RectangleShape grass3(sf::Vector2f(60, 150));
            grass3.setPosition(865, 256);
            grass3.setFillColor(sf::Color::Transparent);
            this->grass.push_back(grass3);

            sf::RectangleShape grass4(sf::Vector2f(30, 200));
            grass4.setPosition(262, 200);
            grass4.setFillColor(sf::Color::Transparent);
            this->grass.push_back(grass4);

            sf::RectangleShape tp(sf::Vector2f(50, 64));
            tp.setPosition(950, 510);
            tp.setFillColor(sf::Color::Transparent);
            this->tp.push_back(tp);

            SpriteMap* pnjItem = new SpriteMap(itemTexture);
            sf::Sprite mySprite = pnjItem->getSprite(1.1, 1.1);
            sf::Sprite* point = &mySprite;
            point->setPosition(835, 130);
            this->sprites.push_back(mySprite);

            sf::RectangleShape getitem(sf::Vector2f(5, 5));
            getitem.setPosition(835, 130);
            getitem.setFillColor(sf::Color::Red);
            this->interactitem.push_back(getitem);

            if (this->map1.size() < 5) {
                this->map1.push_back(&this->walls);
                this->map1.push_back(&this->grass);
                this->map1.push_back(&this->tp);
                this->map1.push_back(&this->interact);
                this->map1.push_back(&this->interactitem);
            }

            if (this->sprites1.size() < 1) {
                this->sprites1.push_back(&this->sprites);
            }

        }

    }
    if (mapId == 1) {

        sf::Texture* itemTexture = new sf::Texture();
        itemTexture->loadFromFile("./img/item.png");

        while (this->map1.size() != 0) {
            for (size_t i = 0; i < this->map1.size(); i++) {
                while (this->map1[i]->size() != 0) {
                    this->map1[i]->pop_back();
                };
            }
            this->map1.pop_back();
        }
        while (this->sprites1.size() != 0) {
            for (size_t i = 0; i < this->sprites1.size(); i++) {
                while (this->sprites1[i]->size() != 0) {
                    this->sprites1[i]->pop_back();
                };
            }
            this->sprites1.pop_back();
        }

        while (this->map3.size() != 0) {
            for (size_t i = 0; i < this->map3.size(); i++) {
                while (this->map3[i]->size() != 0) {
                    this->map3[i]->pop_back();
                };
            }
            this->map3.pop_back();
        }
        while (this->sprites3.size() != 0) {
            for (size_t i = 0; i < this->sprites3.size(); i++) {
                while (this->sprites3[i]->size() != 0) {
                    this->sprites3[i]->pop_back();
                };
            }
            this->sprites3.pop_back();
        }

        if (this->map2.size() == 0) {
            std::cout << "map2 created" << std::endl;
            sf::RectangleShape xall(sf::Vector2f(992, 30));
            xall.setPosition(0, 0);
            xall.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall);

            sf::RectangleShape xall2(sf::Vector2f(20, 672));
            xall2.setPosition(956, 0);
            xall2.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall2);

            sf::RectangleShape xall3(sf::Vector2f(220, 5));
            xall3.setPosition(710, 650);
            xall3.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall3);

            sf::RectangleShape xall4(sf::Vector2f(240, 5));
            xall4.setPosition(215, 650);
            xall4.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall4);

            sf::RectangleShape xall5(sf::Vector2f(200, 150));
            xall5.setPosition(0, 585);
            xall5.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall5);

            sf::RectangleShape xall6(sf::Vector2f(144, 180));
            xall6.setPosition(0, 304);
            xall6.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall6);

            sf::RectangleShape xall7(sf::Vector2f(2, 265));
            xall7.setPosition(0, 30);
            xall7.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall7);

            sf::RectangleShape xall8(sf::Vector2f(28, 310));
            xall8.setPosition(150, 150);
            xall8.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall8);

            sf::RectangleShape xall9(sf::Vector2f(535, 50));
            xall9.setPosition(170, 140);
            xall9.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall9);

            sf::RectangleShape xall10(sf::Vector2f(2, 190));
            xall10.setPosition(280, 320);
            xall10.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall10);

            sf::RectangleShape xall11(sf::Vector2f(375, 10));
            xall11.setPosition(302, 294);
            xall11.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall11);

            sf::RectangleShape xall12(sf::Vector2f(150, 160));
            xall12.setPosition(823, 0);
            xall12.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall12);

            sf::RectangleShape xall13(sf::Vector2f(18, 10));
            xall13.setPosition(502, 374);
            xall13.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall13);

            sf::RectangleShape xall14(sf::Vector2f(2, 80));
            xall14.setPosition(400, 320);
            xall14.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall14);

            sf::RectangleShape xall15(sf::Vector2f(100, 5));
            xall15.setPosition(280, 400);
            xall15.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall15);

            sf::RectangleShape xall16(sf::Vector2f(32, 55));
            xall16.setPosition(175, 175);
            xall16.setFillColor(sf::Color::Transparent);
            this->walls.push_back(xall16);

            sf::RectangleShape xrass(sf::Vector2f(130, 80));
            xrass.setPosition(770, 530);
            xrass.setFillColor(sf::Color::Transparent);
            this->grass.push_back(xrass);

            sf::RectangleShape xrass2(sf::Vector2f(75, 85));
            xrass2.setPosition(32, 180);
            xrass2.setFillColor(sf::Color::Transparent);
            this->grass.push_back(xrass2);

            sf::RectangleShape xrass3(sf::Vector2f(215, 5));
            xrass3.setPosition(150, 70);
            xrass3.setFillColor(sf::Color::Transparent);
            this->grass.push_back(xrass3);

            sf::RectangleShape xrass4(sf::Vector2f(100, 5));
            xrass4.setPosition(428, 120);
            xrass4.setFillColor(sf::Color::Transparent);
            this->grass.push_back(xrass4);

            sf::RectangleShape tp(sf::Vector2f(5, 64));
            tp.setPosition(-25, 510);
            tp.setFillColor(sf::Color::Transparent);
            this->tp.push_back(tp);

            sf::RectangleShape tp2(sf::Vector2f(150, 5));
            tp2.setPosition(512, 670);
            tp2.setFillColor(sf::Color::Transparent);
            this->tp.push_back(tp2);

            SpriteMap* pnjItem = new SpriteMap(itemTexture);
            sf::Sprite mySprite = pnjItem->getSprite(1.1, 1.1);
            sf::Sprite* point = &mySprite;
            point->setPosition(65, 225);
            this->sprites.push_back(mySprite);

            sf::RectangleShape getitem(sf::Vector2f(100, 100));
            getitem.setPosition(65, 235);
            getitem.setFillColor(sf::Color::Red);
            this->interactitem.push_back(getitem);

            /*SpriteMap* pnjItem2 = new SpriteMap(itemTexture);
            sf::Sprite mySprite2 = pnjItem2->getSprite(1.1, 1.1);
            sf::Sprite* point2 = &mySprite2;
            point->setPosition(65, 225);
            this->sprites.push_back(mySprite2);*/

            /*sf::RectangleShape getitem2(sf::Vector2f(5, 5));
            getitem2.setPosition(835, 130);
            getitem2.setFillColor(sf::Color::Red);
            this->interactitem.push_back(getitem2);*/
        }

        if (this->map2.size() < 5) {
            this->map2.push_back(&this->walls);
            this->map2.push_back(&this->grass);
            this->map2.push_back(&this->tp);
            this->map2.push_back(&this->interact);
            this->map1.push_back(&this->interactitem);
        }
    }
    if (mapId == 2) {


        if (this->map3.size() == 0) {

            std::cout << "map3 created" << std::endl;
            while (this->map2.size() != 0) {
                for (size_t i = 0; i < this->map2.size(); i++) {
                    std::cout << "je delete";
                    while (this->map2[i]->size() != 0) {
                        this->map2[i]->pop_back();
                    };
                }
                this->map2.pop_back();
            }

            sf::RectangleShape zall(sf::Vector2f(1, 672));
            zall.setPosition(0, 0);
            zall.setFillColor(sf::Color::Transparent);
            this->walls.push_back(zall);

            sf::RectangleShape zall2(sf::Vector2f(992, 1));
            zall2.setPosition(0, 672);
            zall2.setFillColor(sf::Color::Transparent);
            this->walls.push_back(zall2);

            sf::RectangleShape zall3(sf::Vector2f(522, 205));
            zall3.setPosition(0, 365);
            zall3.setFillColor(sf::Color::Transparent);
            this->walls.push_back(zall3);

            sf::RectangleShape zall4(sf::Vector2f(455, 200));
            zall4.setPosition(0, 0);
            zall4.setFillColor(sf::Color::Transparent);
            this->walls.push_back(zall4);

            sf::RectangleShape zall5(sf::Vector2f(492, 118));
            zall5.setPosition(0, 100);
            zall5.setFillColor(sf::Color::Transparent);
            this->walls.push_back(zall5);

            sf::RectangleShape zall6(sf::Vector2f(200, 400));
            zall6.setPosition(770, 0);
            zall6.setFillColor(sf::Color::Transparent);
            this->walls.push_back(zall6);

            sf::RectangleShape zall7(sf::Vector2f(250, 300));
            zall7.setPosition(720, 112);
            zall7.setFillColor(sf::Color::Transparent);
            this->walls.push_back(zall7);

            sf::RectangleShape zall8(sf::Vector2f(220, 120));
            zall8.setPosition(755, 590);
            zall8.setFillColor(sf::Color::Transparent);
            this->walls.push_back(zall8);

            sf::RectangleShape zall10(sf::Vector2f(50, 2));
            zall10.setPosition(715, 0);
            zall10.setFillColor(sf::Color::Transparent);
            this->walls.push_back(zall10);

            sf::RectangleShape zall9(sf::Vector2f(2, 170)); //this is a wall but is placed where a TP to potential 4th map would be
            zall9.setPosition(990, 415);
            zall9.setFillColor(sf::Color::Transparent);
            this->walls.push_back(zall9);


            sf::RectangleShape tp(sf::Vector2f(175, 5));
            tp.setPosition(480, 5);
            tp.setFillColor(sf::Color::Transparent);
            this->tp.push_back(tp);

            sf::Texture* itemTexture = new sf::Texture();
            itemTexture->loadFromFile("./img/trainer.png");
            SpriteMap* pnjShop = new SpriteMap(itemTexture);
            sf::Sprite mySprite = pnjShop->getSprite(0.45, 0.45);
            sf::Sprite* point = &mySprite;
            point->setPosition(766, 442);
            this->sprites.push_back(mySprite);

            sf::RectangleShape shop(sf::Vector2f(50, 50));
            shop.setPosition(764, 442);
            shop.setFillColor(sf::Color::Red);
            this->interact.push_back(shop);

        }

        if (this->map3.size() < 4) {
            this->map3.push_back(&this->walls);
            this->map3.push_back(&this->grass);
            this->map3.push_back(&this->tp);
            this->map3.push_back(&this->interact);
        }
        if (this->sprites3.size() < 1) {
            this->sprites3.push_back(&this->sprites);

        }
    }
    
}

//Getter

bool Game::getBattle() { return this->battle; }
bool Game::getPause() { return this->pause; }
int Game::getKeyPressed() { return this->keypressed; }
sf::RenderWindow* Game::getWindow() { return this->window; }