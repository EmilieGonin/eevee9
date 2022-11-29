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
    sf::Music music;
    music.openFromFile("./sfx/Music/route.wav");
    music.setLoop(true);
    music.setVolume(15);

    Eevee player(eeveeTexture);
    Enemy enemy(enemyTexture);
    Battle battle(&game, &player, &enemy);
    //sf::Thread thread(&Battle::battle, &battle);

    music.play();
    while (game.isOpen())
    {
        if (game.getBattle()) { //Si un combat est en cours
            //game.draw(player);
            //game.display();
            player.setCoords(227, 60, 60, 79); //Sprite de combat pour Eevee
            player.idle(); //Lancement de l'animation idle
            music.stop();
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
                    player.move();
                }
            }
            else {
                interface.pause();
            }
            
            game.clear();
            interface.map();
            game.draw(player);
            game.display();
        }
    }

    return 0;
}