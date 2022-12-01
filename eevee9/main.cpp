#include "Interface.h"
#include "Battle.h"
#include "Database.h"
#include "Collision.h"

int main()
{
    //Chargement de la base de données
    std::cout << "Loading database..." << std::endl;
    sqlite3* db = getDatabase();
    createEnemies(db);

    Game game;
  

    sf::Texture eeveeTexture, enemyTexture;
    eeveeTexture.loadFromFile("img/player_spritesheet.png");
    enemyTexture.loadFromFile("img/enemies_spritesheet.png");

    Eevee player(eeveeTexture, db);
    Enemy enemy(enemyTexture, db);
    Interface interface(&game, &player, &enemy);
    Battle battle(&game, &player, &enemy, &interface);
    
    interface.start();

    player.spritePosition(850, 510);
    enemy.spritePosition(550, 80);

    while (game.isOpen())
    {
        if (game.getBattle()) { //Si un combat est en cours
       
            interface.stopMusic();
            game.setBattle(battle.battle()); //Conditions de win/loose + set ennemy

            //Si le combat est toujours en cours, on sélectionne un choix
            if (game.getBattle() && !battle.getChoice()) {
                std::cout << "NO CHOICE SELECTED" << std::endl;
                std::cout << "----------" << std::endl << std::endl;
                //Récupération du choix + affichage du background
                battle.setChoice(interface.battle() + 1);
                battle.turn(); //Tour de jeu suivant le choix          
            }            
        }
        else { //Sinon, on vérifie les mouvements du joueur + la pause
            player.setOrientation(game.update(player.getOrientation()));
            if (game.getPause() != true) {
                if (game.getKeyPressed()) {

                    player.update();
                }
                else {
                    player.resetAnimation();
                }
                if (game.isMoving()) {
                    player.move(game.CreateCollision(&player));
                    player.collisionNotMoving(game.CreateCollision(&player));
                    game.randomBattle(game.sethovergrass(&player));
                    interface.changeMap(game.setHoverTp(&player));
                }
            }
            else {
                interface.pause();
            }
            
            game.clear();
            interface.map();
            game.CreateShapes(interface.getMapId());
            //game.drawtile();
            game.draw(player);
            game.display();
        }
    }

    return 0;
}