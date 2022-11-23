#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Epic 9");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile("img/eevee.png"))
    {
        // error...
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(69, 27, 20, 20));

    sf::Sprite sprite2;
    sprite2.setTexture(texture);
    sprite2.setTextureRect(sf::IntRect(96, 27, 20, 20));
    sprite2.scale(10, 10);

    int iter = 0;
    int count = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite2);
        window.display();
    }

    return 0;
}