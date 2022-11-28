#include "Game.h"
#include "Menu.h"
#include "PauseMenu.h"
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

    sf::Texture texture;
    if (!texture.loadFromFile("img/eevee_spritesheet.png"))
    {
        // error...
    }


    Eevee player = Eevee(texture);
    Menu* menu = new Menu(&game.getWindow());
    PauseMenu* pauseMenu = new PauseMenu(&game.getWindow(), &game);
    menu->run_menu();
    delete menu;
    menu = nullptr;

        
        Enemy enemy(texture);
        //player.setCoords(227, 60, 60, 79);
        //Battle battle(&player, &enemy);
        
        while (game.isOpen())
        {
            game.clear();
            game.draw(player);

            player.setOrientation(game.update(player.getOrientation()));
            if (game.getPause() != true) {
                if (game.getKeyPressed()) {
                    player.update();
                }
                else {

                    player.resetAnimation();
                }
                if (game.isMoving()) {
                    player.move();
                }
            }
            else {
                
                pauseMenu->menu = true;
                pauseMenu->run_menu();
               
            }

            //player.idle();
            game.draw(player);
            game.display();
        }
    
    return 0;
}