#include "Interface.h"
#include "Battle.h"
#include "Database.h"

int main()
{
    //Chargement de la base de données
    std::cout << "Loading database...\n";
    sqlite3* db = getDatabase();

    Game game;
    Interface interface(&game);
    interface.start();

    sf::Texture eeveeTexture, enemyTexture;
    eeveeTexture.loadFromFile("img/eevee_spritesheet.png");
    enemyTexture.loadFromFile("img/eevee_spritesheet.png"); //temp

    Eevee player(eeveeTexture);
    Enemy enemy(enemyTexture);
    Battle battle(&player, &enemy);
    //sf::Thread thread(&Battle::battle, &battle);
    //player.setCoords(227, 60, 60, 79);
        
    while (game.isOpen())
    {
        //battle.setFighting(true);

        //Si un combat commence, on change d'écran
        if (battle.isFighting()) {
            player.idle();
            battle.battle();
            //thread.launch();
            //Show menu fighting
        }
        //Sinon, on vérifie les mouvements du joueur + la pause
        else {
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
                interface.pause();
            }
        }

        game.clear();
        game.draw(player);
        game.display();
    }

    return 0;
}