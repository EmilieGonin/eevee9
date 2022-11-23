#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Eevee.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Epic 9");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile("img/moving.png"))
    {
        // error...
    }

    Eevee player = Eevee(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        player.update();
        window.draw(player.getSprite());
        window.display();
    }

    return 0;
}