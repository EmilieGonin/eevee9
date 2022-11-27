#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Eevee.h"
#include "Enemy.h"
#include "Battle.h"
#include "Game.h"
#include "Database.h"
#include <iostream>

//void checkPosition() {
//
//}
int main()
{
    //Chargement de la base de données
    std::cout << "Loading database...\n";
    sqlite3* db = getDatabase();

    Game game;

    sf::Texture texture;
    if (!texture.loadFromFile("img/trainer.png"))
    {
        // error...
    }

    Eevee player(texture);
    Enemy enemy(texture);
    Battle battle(&player, &enemy);

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