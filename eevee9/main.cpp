#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Eevee.h"
#include "Game.h"
#include <iostream>

//void checkPosition() {
//
//}
int main()
{
    Game game;

    sf::Texture texture;
    if (!texture.loadFromFile("img/trainer.png"))
    {
        // error...
    }

    Eevee player = Eevee(texture);

    while (game.isOpen())
    {
        game.clear();
        player.setOrientation(game.update(player.getOrientation()));
        if (game.getKeyPressed()) {
            player.update();
        }
        else {
            player.resetAnimation();
        }
        if (game.isMoving()) {
            player.move();
        }

        game.draw(player);
        game.display();
    }
    return 0;
}