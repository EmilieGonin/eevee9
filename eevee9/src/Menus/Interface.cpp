#include "Interface.h"

Interface::Interface(Game* game, Eevee* eevee, Enemy* enemy) {
    //Game & Window
    this->_game = game;
    this->eevee = eevee;
    this->enemy = enemy;
    this->window = this->_game->getWindow();

    //Images & Shapes
    this->image = new sf::Texture();
    this->bg = new sf::Sprite();
    this->lifebar = new sf::Texture();
    this->myHpBar = new sf::Sprite();
    this->winclose = new sf::RectangleShape();


    this->hpBarLength = 133;
    this->count = 40;

    this->winclose->setSize(sf::Vector2f(34.5, 39));
    this->winclose->setPosition(1767, 58.5);
    this->winclose->setFillColor(sf::Color::Transparent);


    //Font & Texts
    this->sizes = { 36,36,36 };
    this->font = new sf::Font();
    this->font2 = new sf::Font();
    font->loadFromFile("./src/Menus/Hansip.otf");
    font2->loadFromFile("./src/Menus/Pok.ttf");

    //Sounds & Music
    this->music.setLoop(true);
    this->music.setVolume(10);
    this->buffer.loadFromFile("./sfx/sounds/button.wav");
    this->button.setBuffer(this->buffer);
    this->button.setVolume(30);
    this->bufferStart.loadFromFile("./sfx/sounds/start.wav");
    this->startButton.setBuffer(this->bufferStart);
    this->startButton.setVolume(30);

    //Misc
    this->pos = 0;
    this->pressed = this->theselect = this->pauseMenu = this->battleMenu = this->display = this->state =  false;
    
    this->startMenu = true;
}

Interface::~Interface() {
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void Interface::loop_events() {
    sf::Event event;
    texts[this->pos].setOutlineThickness(10);
    //std::cout << "pos : " << this->pos << std::endl;

    if (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !this->pressed) {
            if (this->pos < this->options.size() - 1) {
                this->button.play();
                texts[this->pos].setOutlineThickness(0);
                ++pos;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !this->pressed) {
            if (this->pos > 0) {
                this->button.play();
                texts[this->pos].setOutlineThickness(0);
                --pos;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !this->pressed) {
            std::cout << "---- OPTION SELECTED :" << options[this->pos] << std::endl;

            if (this->startMenu == true) {
                startOptions();
            }
            else if (this->pauseMenu == true) {
                pauseOptions();
            }
            else if (this->display == true) {

                this->button.play();
                beginningOptions();

            }
            else if (this->battleMenu == true) {
                this->button.play();
                battleOptions();
                this->choice = pos;

            }
        
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                this->pressed = true;
            }
            this->pressed = false;
        }
    }
}

void Interface::draw_all() {
    this->window->draw(*bg);
    

    if(this->battleMenu == true)
    {
        for (auto t : texts) {
            t.setCharacterSize(24);
            t.setFillColor(sf::Color::Black);
            t.setOutlineColor(sf::Color::White);
            this->window->draw(t);
        }
        this->window->draw(*myHpBar);
        sf::Text hp;
        hp.setFont(*font2);
        hp.setString(std::to_string(this->eevee->getHP()) + "      " + std::to_string(this->eevee->getMaxHP()));
        hp.setFillColor(sf::Color::Black);
        hp.setCharacterSize(23);
        hp.setPosition(875, 464);
        this->window->draw(hp);

        sf::RectangleShape myHp;


        myHp.setSize(sf::Vector2f(this->hpBarLength, 11));
        myHp.setPosition(846, 448);
        myHp.setFillColor(sf::Color::Green);
        window->draw(myHp);
 

        this->eevee->idle();
        this->enemy->idle();
        this->window->draw(this->eevee->getSprite(7, 7));
        this->window->draw(this->enemy->getSprite(4, 4));
    }
    else {
        for (auto t : texts) {
            
            this->window->draw(t);
        }
    }
    
    this->window->display();
}
void Interface::drawComment(std::string comment, bool win) {


    if (win) {

        if (this->music.getStatus() != 2) {
            this->music.openFromFile("./sfx/Music/victory.wav");
            this->music.play();
        }
    }
    this->window->draw(*bg);
    this->window->draw(*myHpBar);
    

    sf::RectangleShape myHp;

    std::cout << this->hpBarLength;
    myHp.setSize(sf::Vector2f(this->hpBarLength, 11));
    float haha = 133 * this->eevee->getHP() / this->eevee->getMaxHP();
    std::cout << haha;
    /*while(haha != this->hpBarLength) {
        std::cout << "hahaha" << std::endl;
        this->window->draw(myHp);  
        myHp.setSize(sf::Vector2f(this->hpBarLength, 11));
  
        this->hpBarLength = this->hpBarLength - 0.1;
    }*/

 
    myHp.setPosition(846, 448);
    myHp.setFillColor(sf::Color::Green);
    window->draw(myHp);
    
    
    

    sf::Text text;
    text.setFont(*font2);
    text.setString(comment);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(24);
    text.setPosition(50, 600);
    this->window->draw(text);

    sf::Text hp;
    hp.setFont(*font2);
    hp.setString(std::to_string(this->eevee->getHP()) + "      " + std::to_string(this->eevee->getMaxHP()));
    hp.setFillColor(sf::Color::Black);
    hp.setCharacterSize(23);
    hp.setPosition(875, 464);
    this->window->draw(hp);

   
    this->eevee->idle();
    this->enemy->idle();
    this->window->draw(this->eevee->getSprite(7, 7));
    this->window->draw(this->enemy->getSprite(4, 4));

    

   

    for (auto t : texts) {
        this->window->draw(t);
    }
    this->window->display();
    
}

void Interface::start() {
    this->music.openFromFile("./sfx/Music/title.wav");
    this->music.play();

    //Background
    this->image->loadFromFile("./img/titleScreen.png");
    this->bg->setTexture(*image);

    //Texts
    this->options = { "Play", "Options", "Quit" };
    this->coords = { {490,290},{463,400},{490,515} };
    setTexts(options.size());

    while (this->startMenu == true) {
        loop_events();
        draw_all();
    }

    this->music.stop();
}

void Interface::startOptions() {
    if (this->pos == 0) {
        this->startButton.play();
        this->startMenu = false;
    }

    if (this->pos == 2) {
        this->window->close();
    }
}

void Interface::pause() {
    this->button.play();
    this->pauseMenu = true;
    this->image->loadFromFile("./img/PauseMenu.png");
    this->bg->setTexture(*image);

    //Texts
    this->options = { "Resume", "Save", "Quit" };
    this->coords = { {830,190},{830,300},{830,415} };
    setTexts(options.size());

    while (this->pauseMenu == true) {
        loop_events();
        draw_all();
    }
}

void Interface::pauseOptions() {
    if (this->pos == 0) {
        this->button.play();
        this->_game->setPause(false);
        this->pauseMenu = false;
    }
    else if (this->pos == 1) {
        this->button.play();
        //sauvegarde
    }
    else if (this->pos == 2) {
        this->button.play();
        this->window->close();
    }
}

int Interface::battle() {

    std::cout << "coucou";
    this->image->loadFromFile("./img/battle1.png");
    this->bg->setTexture(*image);
    this->lifebar->loadFromFile("./img/lifebar.png");
    this->myHpBar->setTexture(*lifebar);
    this->myHpBar->setPosition(802, 444);


    this->options = { "" };
    this->coords = { {0,0} };
    setTexts(options.size());

    this->battleMenu = true;
        
    std::cout << "je passe ici" << std::endl;
    //Texts
    this->options = { "Attack", "Escape" };
    this->coords = { {800,525},{800,575} };
    setTexts(options.size());

    while(this->battleMenu ==true)
    {

        loop_events();
        draw_all();


    }

    

  
    return this->choice;
}

void Interface::displayComment(std::string comment, bool win) {
    this->display = true;
    this->image->loadFromFile("./img/battle.png");
    this->bg->setTexture(*image);



    this->options = { "" };
    this->coords = { {0,0} };
    setTexts(options.size());
    while (this->display == true)
    {
        pos = 0;
        loop_events();
        drawComment(comment, win);
    }
    if (win) {
        this->music.stop();
    }
}

void Interface::map() {
    if (!this->battleMenu && this->music.getStatus() != 2) {
        this->music.openFromFile("./sfx/Music/route.wav");
        this->music.play();
    }
    else if (this->battleMenu) {
        this->music.stop();
    }

    this->image->loadFromFile("./img/map.png");
    this->bg->setTexture(*image);
    this->window->draw(*bg);
}

void Interface::battleOptions() {
    this->battleMenu = false;
}

void Interface::beginningOptions() {
    std::cout << "je passe ici" << std::endl;
    this->display = false;
}

void Interface::stateOptions() {
    std::cout << "je passe ici" << std::endl;
    this->state = false;
}

//Setters

void Interface::stopMusic() {
    if (this->music.getStatus() == 2) {
        this->music.stop();
    }
}

void Interface::setPauseMenu(bool pause) {
    this->pauseMenu = pause;
}

void Interface::setTexts(int size) {
    this->texts.resize(size);
    for (std::size_t i{}; i < this->texts.size(); ++i) {
        this->texts[i].setFont(*font);
        this->texts[i].setFillColor(sf::Color::White);
        this->texts[i].setString(this->options[i]);
        this->texts[i].setCharacterSize(this->sizes[i]);
        this->texts[i].setOutlineColor(sf::Color(186, 84, 0));
        this->texts[i].setPosition(this->coords[i]);
    }
}

//Getters

int Interface::getPos() { return this->pos; }
bool Interface::getStartMenu() { return this->startMenu; }
bool Interface::getPauseMenu() { return this->pauseMenu; }
bool Interface::getBattleMenu() { return this->battleMenu; }