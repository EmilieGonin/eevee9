#include "Menu.h"


Menu::Menu(sf::RenderWindow* window) {

    this->winclose = new sf::RectangleShape();
    this->font = new sf::Font();
    this->image = new sf::Texture();
    this->bg = new sf::Sprite();    
    this->menu = true;
    this->window = window;

    set_values();
}

Menu::~Menu() {

    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void Menu::set_values() {


    pos = 0;
    pressed = theselect = false;
    this->buffer.loadFromFile("./sfx/sounds/button.wav");
    button.setBuffer(this->buffer);
    this->music.openFromFile("./sfx/Music/title.wav");
    this->music.setLoop(true);
    font->loadFromFile("./src/Menus/Hansip.otf");
    image->loadFromFile("./img/titleScreen.png");

    bg->setTexture(*image);
    bg->setScale(1, 1);

    options = { "Play", "Options", "Quit" };
    texts.resize(3);
    coords = { {490,290},{463,400},{490,515} };
    sizes = { 36,36,36 };

    for (std::size_t i{}; i < texts.size(); ++i) {
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setPosition(coords[i]);
    }
    texts[1].setOutlineThickness(10);
    pos = 1;

    winclose->setSize(sf::Vector2f(34.5, 39));
    winclose->setPosition(1767, 58.5);
    winclose->setFillColor(sf::Color::Transparent);

}

void Menu::loop_events() {
    sf::Event event;

    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
        }

      
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed) {
            
            if (pos < 2) {
                this->button.play();
                ++pos;
                pressed = true;
                texts[pos].setOutlineThickness(10);
                texts[pos - 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed) {
            if (pos > 0) {
                this->button.play();
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
                this->menu = false;
            }

            if (pos == 2) {
                this->music.play();
                this->window->close();
            }
            std::cout << options[pos] << '\n';
        }

    }
}

    void Menu::draw_all() {
        this->window->clear();
        this->window->draw(*bg);
        for (auto t : texts) {
            this->window->draw(t);
        }
        this->window->display();
    }

    void Menu::run_menu() {
        this->music.play();
        while (this->menu == true) {
            
            loop_events();
            draw_all();
        }
        this->music.play();
    }

    bool Menu::getPlay() {
        return this->menu;
    }

    
