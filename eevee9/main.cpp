#include "Interface.h"
#include "Battle.h"
#include "Database.h"
#include "collision.h"

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

    Interface interface(&game);
    interface.start();
    
    sf::RectangleShape wall(sf::Vector2f(992, 75));
    wall.setPosition(0, 0);
    wall.setFillColor(sf::Color::Red);
    collision rectangleTile(wall);
    
    sf::Texture eeveeTexture, enemyTexture;
    eeveeTexture.loadFromFile("img/eevee_spritesheet.png");
    enemyTexture.loadFromFile("img/eevee_spritesheet.png"); //temp

    Eevee player(eeveeTexture);
    Enemy enemy(enemyTexture);
    Battle battle(&game, &player, &enemy);
    Interface interface(&game, &player);
    interface.start();

    player.spritePosition(850, 510);

    while (game.isOpen())
    {
        if (game.getBattle()) { //Si un combat est en cours
            interface.stopMusic();
            player.spritePosition(2, 300); //Déplace Eevee au bon endroit
            player.setCoords(227, 60, 60, 79); //Sprite de combat pour Eevee
            game.setBattle(battle.battle()); //Conditions de win/loose

            //Si le combat est toujours en cours, on sélectionne un choix
            if (game.getBattle() && !battle.getChoice()) {
                std::cout << "NO CHOICE SELECTED" << std::endl;
                std::cout << "----------" << std::endl << std::endl;
                //Récupération du choix + affichage du background
                game.draw(player);
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
            game.display();
        }
    }

    return 0;
}