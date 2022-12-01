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
    this->pos = 0; //Position du curseur (choix)
    this->pressed = this->pauseMenu = this->battleMenu = this->display = this->evolveMenu = false;
    this->startMenu = true;

    //Fetch mapId from database
    this->mapId = this->eevee->getMap();
}

Interface::~Interface() {
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void Interface::loop_events() {
    sf::Event event;
    texts[this->pos].setOutlineThickness(10); //On souligne le choix actuel
    //std::cout << "pos : " << this->pos << std::endl;

    if (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !this->pressed) {
            if (this->pos < this->options.size() - 1) { //Ne pas dépasser le max de choix
                this->button.play(); //Son du bouton
                //On retire le contour du choix actuel, puis on change de choix
                texts[this->pos].setOutlineThickness(0);
                ++pos;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !this->pressed) {
            if (this->pos > 0) {
                this->button.play(); //Son du bouton
                //On retire le contour du choix actuel, puis on change de choix
                texts[this->pos].setOutlineThickness(0);
                --pos;
            }
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !this->pressed) {
            std::cout << "j'escape";
            texts[this->pos].setOutlineThickness(0);
            if (this->evolveMenu == true)
            {
                this->battleMenu = true;
                this->evolveMenu = false;
            }

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !this->pressed) {
            std::cout << "---- OPTION SELECTED : " << options[this->pos] << std::endl;
            texts[this->pos].setOutlineThickness(0);
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
            else if (this->evolveMenu == true) {
                this->button.play();
                evolveOptions();
                
                this->choice = pos+2;
                std::cout << this->choice;
            }
            
            //On évite que le choix soit fait avant relâchement de la touche
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                this->pressed = true;
            }
            this->pressed = false;
        }
    }
}

void Interface::drawEevee() {
    //Définis la texture et les frames de Eevee (évolué ou non)
    if (this->eevee->getEeveelution()) {
        this->eevee->setY(227 + (96 * this->eevee->getEeveelution()));
    }
    else {
        this->eevee->setY(227);
        this->eevee->setSpriteFrames(79);
    }

    //Définis les coordonnées de combat de Eeevee
    this->eevee->spritePosition(-50, 125); //Déplace Eevee au bon endroit
    this->eevee->setCoords(this->eevee->getY(), 96, 96, this->eevee->getSpriteFrames());

    this->eevee->idle();
    this->window->draw(this->eevee->getSprite(6, 6));
}

void Interface::draw_all() {
    this->window->draw(*bg); //Background
    

    if (this->battleMenu == true ||this->evolveMenu) {
        for (auto t : texts) { //Draw tous les textes
            t.setCharacterSize(24);
            t.setFillColor(sf::Color::Black);
            t.setOutlineColor(sf::Color::White);
            this->window->draw(t);
        }

        sf::Text hp;
        hp.setFont(*font2);
        hp.setString(std::to_string(this->eevee->getHP()) + "      " + std::to_string(this->eevee->getMaxHP()));
        hp.setFillColor(sf::Color::Black);
        hp.setCharacterSize(23);
        hp.setPosition(875, 464);
        this->window->draw(hp);
        
        sf::RectangleShape myHp;

        
        if (this->hpBarLength == 0) {
            this->hpBarLength = 133;
        }
 
        myHp.setSize(sf::Vector2f(this->hpBarLength, 11));
        myHp.setPosition(846, 448);
        myHp.setFillColor(sf::Color::Green);
        window->draw(myHp);
 

        sf::RectangleShape ennemyBarHp;

        if (this->enemy->getMaxHP() == this->enemy->getHP()) {
            this->ennemyHpBarLength = 150;
        }
        ennemyBarHp.setSize(sf::Vector2f(this->ennemyHpBarLength, 11));
        ennemyBarHp.setPosition(145, 94);
        ennemyBarHp.setFillColor(sf::Color::Green);
        window->draw(ennemyBarHp);

        this->drawEevee();
        this->enemy->idle();
        this->window->draw(this->enemy->getSprite(4, 4));
    }
    else {
        for (auto t : texts) { 
            this->window->draw(t);
        }
    }

    this->window->display(); //On affiche tout
}

void Interface::drawComment(std::string comment, bool win) {
    if (win) {
        if (this->music.getStatus() != 2) {
            this->music.openFromFile("./sfx/Music/victory.wav");
            this->music.play();
        }
    }
    this->window->draw(*bg);

 
    sf::RectangleShape myHp;
    this->hpBarLength = this->hpBarLength * 100;
    int hpBarToGet = 133 * this->eevee->getHP() / this->eevee->getMaxHP() * 100;

   if(hpBarToGet != this->hpBarLength) {
        myHp.setSize(sf::Vector2f(this->hpBarLength, 11));
        this->window->draw(myHp);  
        this->hpBarLength = this->hpBarLength - 1;
    }

    this->hpBarLength = this->hpBarLength / 100;
    myHp.setPosition(846, 448);
    myHp.setFillColor(sf::Color::Green);
    myHp.setSize(sf::Vector2f(this->hpBarLength, 11));
    window->draw(myHp);

    sf::RectangleShape ennemyHp;

    this->ennemyHpBarLength = this->ennemyHpBarLength * 100;
    int ennemyhpBarToGet = 150 * this->enemy->getHP() / this->enemy->getMaxHP() * 100;

    if (ennemyhpBarToGet != this->ennemyHpBarLength) {


        ennemyHp.setSize(sf::Vector2f(this->ennemyHpBarLength, 11));
        this->window->draw(ennemyHp);
        this->ennemyHpBarLength = this->ennemyHpBarLength - 1;
    }


    this->ennemyHpBarLength = this->ennemyHpBarLength / 100;
    ennemyHp.setPosition(145, 94);
    ennemyHp.setFillColor(sf::Color::Green);
    ennemyHp.setSize(sf::Vector2f(this->ennemyHpBarLength, 11));
    window->draw(ennemyHp);


    sf::Text text;
    text.setFont(*font2);
    text.setString(comment);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(26);
    text.setPosition(50, 600);
    this->window->draw(text);

    sf::Text hp;
    hp.setFont(*font2);
    hp.setString(std::to_string(this->eevee->getHP()) + "      " + std::to_string(this->eevee->getMaxHP()));
    hp.setFillColor(sf::Color::Black);
    hp.setCharacterSize(23);
    hp.setPosition(875, 464);
    this->window->draw(hp);

    this->drawEevee();

    if(!win)
    {
        this->enemy->idle();
        this->window->draw(this->enemy->getSprite(4, 4));
    }
 

    for (auto t : texts) {
        this->window->draw(t);
    }

    this->window->display(); //On affiche tout
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

void Interface::evolve() {


    //Background
    this->image->loadFromFile("./img/battle1.png");
    this->bg->setTexture(*image);


    this->options = {""};
    this->coords = { {1,1} };
    if(this->eevee->canEvolve())
    {
        this->options.erase(this->options.begin());
        this->coords.erase(this->coords.begin());
        if (this->eevee->getFire() > 0) {
            this->options.push_back("Fire");
            this->coords.push_back({ 490,290 });
        }
        if (this->eevee->getWater() > 0) {
            this->options.push_back("Water");
            this->coords.push_back({ 463,400 });
        }
        if (this->eevee->getThunder() > 0) {
            this->options.push_back("Thunder");
            this->coords.push_back({ 490,515 });
        }
    }
    //Texts

    setTexts(options.size());

    pos = 0;
    while (this->evolveMenu == true) {

        loop_events();
        draw_all();
    }

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
        this->eevee->setMapPosition(this->eevee->getSprite(2, 2).getPosition());
        sqlite3* db = getDatabase();
        setSave(db, this->eevee->getHP(), this->eevee->getWater(), this->eevee->getThunder(), this->eevee->getFire(), this->mapId, this->eevee->getMapPosition().x, this->eevee->getMapPosition().y, this->eevee->getOrientation());
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


    this->options = { "" };
    this->coords = { {0,0} };
    setTexts(options.size());

    this->battleMenu = true;
        
    std::cout << "je passe ici" << std::endl;

    //Texts

    while(this->battleMenu == true)
    {
        this->options = { "Attack", "Escape", "Evolve" };
        this->coords = { {800,525},{800,575},{800,630} };
        setTexts(options.size());
        loop_events();
        draw_all();
        if (this->evolveMenu == true)
        {
            std::cout << "je suis en train d'evolve ";
           
            evolve();
        }

    }
    std::cout << this->choice;

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

    this->image->loadFromFile(this->mapLinks[this->mapId]);
    this->bg->setTexture(*image);
    this->window->draw(*bg);
}

void Interface::battleOptions() {
    this->battleMenu = false;
    if (pos == 2) {
        this->evolveMenu = true;
    }
}

void Interface::beginningOptions() {
    std::cout << "je passe ici" << std::endl;
    this->display = false;
}

void Interface::evolveOptions() {
    
    this->evolveMenu = false;
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

void Interface::setMap(int nb) {
    this->mapId = nb;
}

void Interface::changeMap(bool colTp) {
    if (colTp) {
        if (this->mapId == 0) {
            setMap(1);
            this->eevee->spritePosition(50, this->eevee->getSprite(2,2).getPosition().y);
        }
        if (this->mapId == 1 && this->eevee->getOrientation() == LEFT ) {
            setMap(0);
            this->eevee->spritePosition(880, this->eevee->getSprite(2, 2).getPosition().y);
        }
    }
}
//Getters

int Interface::getPos() { return this->pos; }
bool Interface::getStartMenu() { return this->startMenu; }
bool Interface::getPauseMenu() { return this->pauseMenu; }
bool Interface::getBattleMenu() { return this->battleMenu; }
bool Interface::getMapId() { return this->mapId; }
