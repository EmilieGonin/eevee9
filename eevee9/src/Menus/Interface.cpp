#include "Interface.h"

Interface::Interface(Game* game) {
    //Game & Window
    this->_game = game;
    this->window = this->_game->getWindow();

    //Images & Shapes
    this->image = new sf::Texture();
    this->bg = new sf::Sprite();
    this->winclose = new sf::RectangleShape();
    this->winclose->setSize(sf::Vector2f(34.5, 39));
    this->winclose->setPosition(1767, 58.5);
    this->winclose->setFillColor(sf::Color::Transparent);

    //Font & Texts
    this->sizes = { 36,36,36 };
    this->font = new sf::Font();
    font->loadFromFile("./src/Menus/Hansip.otf");

    //Sounds & Music
    this->music.openFromFile("./sfx/Music/title.wav");
    this->music.setLoop(true);
    this->music.setVolume(10);
    this->buffer.loadFromFile("./sfx/sounds/button.wav");
    this->button.setBuffer(this->buffer);
    this->button.setVolume(30);

    //Misc
    this->pos = 0;
    this->pressed = this->theselect = this->pauseMenu = this->battleMenu = false;
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
    this->pressed = false;
    //std::cout << "pos : " << this->pos << std::endl;

    if (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
        }
      
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !this->pressed) {
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
            std::cout << options[this->pos] << std::endl;
            this->pressed = true;

            if (this->startMenu == true) {
                startOptions();
            }
            else if (this->pauseMenu == true) {
                pauseOptions();
            }
            else if (this->battleMenu == true) {
                battleOptions();
            }
        }
    }
}

void Interface::draw_all() {
    this->window->draw(*bg);
    for (auto t : texts) {
        this->window->draw(t);
    }
    this->window->display();
}

void Interface::start() {
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
}

void Interface::startOptions() {
    if (this->pos == 0) {
        this->music.stop();
        this->startMenu = false;
    }

    if (this->pos == 2) {
        this->music.stop();
        this->window->close();
    }
}

void Interface::pause() {
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
        this->_game->setPause(false);
        this->pauseMenu = false;
    }
    else if (this->pos == 1) {
        //sauvegarde
    }
    else if (this->pos == 2) {
        this->window->close();
    }
}

int Interface::battle() {
    this->battleMenu = true;
    //std::cout << "choice : " << choice << std::endl;
    //this->image->loadFromFile("./img/battle.png");
    //this->bg->setTexture(*image);

    //Texts
    this->options = { "Attack", "Escape" };
    this->coords = { {830,190},{830,300} };
    setTexts(options.size());

    while (this->battleMenu == true) {
        loop_events();
        draw_all();
    }

    int choice = pos;
    //this->pos = 0;
    return choice;
}

void Interface::battleOptions() {
    this->battleMenu = false;
}

//Setters

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

void Interface::map() {

    this->image->loadFromFile("./img/map.png");
    this->bg->setTexture(*image);
     this->window->draw(*bg);
    
}

//Getters

int Interface::getPos() { return this->pos; }
bool Interface::getStartMenu() { return this->startMenu; }
bool Interface::getPauseMenu() { return this->pauseMenu; }
bool Interface::getBattleMenu() { return this->battleMenu; }