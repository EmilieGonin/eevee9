#include "Game.h"
#include "Menu.h"
#include "Battle.h"
#include "Database.h"

//void checkPosition() {
//
//
//}
int main()
{
    //Chargement de la base de données
    std::cout << "Loading database...\n";
    sqlite3* db = getDatabase();

    Game game;
    Menu* menu = new Menu(&game.getWindow());
    menu->run_menu();
        sf::Texture texture;
        if (!texture.loadFromFile("img/eevee_spritesheet.png"))
        {
            // error...
        }

        Eevee player = Eevee(texture);
        Enemy enemy(texture);
        //player.setCoords(227, 60, 60, 79);
        //Battle battle(&player, &enemy);
        
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

            //player.idle();
            game.draw(player);
            game.display();
        }
    
    return 0;
}