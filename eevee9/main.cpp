#include "Interface.h"
#include "Battle.h"
#include "Database.h"
#include "Collision.h"

/*Todo list
- Mettre un délai au lancement du combat avant l'apparition de l'écran ?
- Déplacer correctement le menu de combat
- Afficher PV et nom des Pokémon lors du combat
- Relier inventaire Eevee au menu pause
- Save position eevee sur la map et remettre eevee au bon endroit
*/

int main()
{
    //Chargement de la base de données
    std::cout << "Loading database...\n";
    sqlite3* db = getDatabase();
    createEnemies(db);

    Game game;

    sf::RectangleShape wall(sf::Vector2f(992, 75));
    wall.setPosition(0, 0);
    wall.setFillColor(sf::Color::Red);
    Collision rectangleTile(wall);
    
    sf::Texture eeveeTexture, enemyTexture;
    eeveeTexture.loadFromFile("img/eevee_spritesheet.png");
    enemyTexture.loadFromFile("img/ponchiot.png"); //temp

    Eevee player(eeveeTexture);
    Enemy enemy(enemyTexture);
    Interface interface(&game, &player, &enemy);
    Battle battle(&game, &player, &enemy, &interface);
    
    interface.start();

    player.spritePosition(850, 510);
    enemy.spritePosition(50, 500); 
    enemy.setCoords(0, 96, 96, 64);

    while (game.isOpen())
    {
        if (game.getBattle()) { //Si un combat est en cours

            interface.stopMusic();
            player.spritePosition(2, 200); //Déplace Eevee au bon endroit
            player.setCoords(227, 60, 60, 79); //Sprite de combat pour Eevee
            //Sprite de combat pour Eevee
            game.setBattle(battle.battle()); //Conditions de win/loose
            //Si le combat est toujours en cours, on sélectionne un choix
            if (game.getBattle() && !battle.getChoice()) {
                std::cout << "NO CHOICE SELECTED" << std::endl;
                std::cout << "----------" << std::endl << std::endl;
                //Récupération du choix + affichage du background
                battle.setChoice(interface.battle() + 1);
                battle.turn(); //Tour de jeu suivant le choix          
            }            
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
                    player.move(rectangleTile.getcollision(&player));
                }
            }
            else {
                interface.pause();
            }
            
            game.clear();
            interface.map();
            game.drawtile(rectangleTile.gettile());
            game.draw(player); 
            game.draw(enemy);
            game.display();
        }
    }

    return 0;
}