#include "Interface.h"
#include "Battle.h"
#include "Database.h"
#include "Collision.h"

int main()
{
    std::cout << "Loading database..." << std::endl;
    sqlite3* db = getDatabase();
    createDatabase(db); //Chargement de la base de données

    Game game;
  
    sf::Texture eeveeTexture, enemyTexture;
    eeveeTexture.loadFromFile("img/player_spritesheet.png");
    enemyTexture.loadFromFile("img/enemies_spritesheet.png");

    Eevee player(eeveeTexture, db);
    Enemy enemy(enemyTexture, db);
    Interface interface(&game, &player, &enemy);
    Battle battle(&game, &player, &enemy, &interface);
    
    interface.start(); //Lancement du menu de démarrage

    player.spritePosition(player.getMapPosition().x, player.getMapPosition().y);

    while (game.isOpen()) {
        if (game.getBattle()) { //Si un combat est en cours
            interface.stopMusic();
            game.setBattle(battle.battle()); //Conditions de win/loose + set ennemy

            //Si le combat est toujours en cours, on sélectionne un choix
            if (game.getBattle() && !battle.getChoice()) {
                std::cout << "NO CHOICE SELECTED" << "----------" << std::endl;
                //Récupération du choix + affichage du background
                battle.setChoice(interface.battle() + 1);
                battle.turn(); //Tour de jeu suivant le choix          
            }            
        }
        else { //Sinon, on vérifie les mouvements du joueur + la pause
            player.setOrientation(game.update(player.getOrientation()));

            if (game.getPause() != true && interface.getShop() != true) { //Si le jeu n'est pas en pause
                if (game.getKeyPressed()) { //On vérifie les touches pressées
                    player.update();
                }
                else {
                    player.resetAnimation();
                }

                if (game.isMoving()) { //On vérifie si le sprite doit bouger
                    player.move(game.CreateCollision(&player));
                    player.collisionNotMoving(game.CreateCollision(&player));
                    player.collisionNotMoving(game.setColSprites(&player));
                    game.randomBattle(game.sethovergrass(&player));
                    interface.changeMap(game.setHoverTp(&player));
                   
                    
                }
                interface.openShop(game.setInteractShop(&player));
            }
            else if(game.getPause()) {
                interface.pause();
            }
            else if (interface.getShop()) {
                interface.shop();
                
            }
            
            game.clear();
            interface.map(); //Création de la map et des collisions
            game.drawtile(); //Debug only - voir où sont placées nos collisions
            game.draw(player);
            game.display();
        }
    }

    return 0;
}