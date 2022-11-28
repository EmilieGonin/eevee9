
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow* window, Game* game) {

    this->winclose = new sf::RectangleShape();
    this->font = new sf::Font();
    this->image = new sf::Texture();
    this->bg = new sf::Sprite();
    this->menu = true;
    this->window = window;
    this->timer = 0;
    this->game = game;
    
    set_values();
}

PauseMenu::~PauseMenu() {

    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void PauseMenu::set_values() {


    pos = 0;
    pressed = theselect = false;
    font->loadFromFile("./src/Menus/Hansip.otf");
    image->loadFromFile("./img/titleScreen.png");

 

    options = { "Play", "Options", "Quit" };
    texts.resize(3);
    coords = { {490,290},{463,400},{490,515} };
    sizes = { 36,36,36 };

    for (std::size_t i{}; i < texts.size(); ++i) {
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Red);
        texts[i].setPosition(coords[i]);
    }
    texts[1].setOutlineThickness(10);
    pos = 1;

    winclose->setSize(sf::Vector2f(34.5, 39));
    winclose->setPosition(1767, 58.5);
    winclose->setFillColor(sf::Color::Transparent);

}

void PauseMenu::loop_events() {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed && this->timer == 0 ) {
            this->timer = 20;
            if (pos < 2) {
                ++pos;
                pressed = true;
                texts[pos].setOutlineThickness(10);
                texts[pos - 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed && this->timer == 0) {
            this->timer = 20;
            if (pos > 0) {
                --pos;
                pressed = true;
                texts[pos].setOutlineThickness(10);
                texts[pos + 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect) {
            theselect = true;
        
            if (pos == 0) {
                this->game->setPause(false);
            }
            if (pos == 1 ){
               //sauvegarde
            }

            if (pos == 2) {

                this->window->close();
            }
            std::cout << options[pos] << '\n';
        }
        if (timer != 0) {
            this->timer--;
        }
        
        std::cout << this->timer;

    
}

void PauseMenu::draw_all() {
    
  
    for (auto t : texts) {
        this->window->draw(t);
    }
    /*this->window->display();*/
}

void PauseMenu::run_menu() {
 

        loop_events();
        draw_all();
    
}

bool PauseMenu::getPlay() {
    return this->menu;
}


