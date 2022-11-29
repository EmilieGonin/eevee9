#include "Interface.h"
#include "Battle.h"
#include "Database.h"
#include "Tile.h"

int main()
{
    //Chargement de la base de données
    std::cout << "Loading database...\n";
    sqlite3* db = getDatabase();

    Game game;
    Interface interface(&game);
    interface.start();
    sf::RectangleShape rectangle(sf::Vector2f(992, 90));
    sf::Texture eeveeTexture, enemyTexture;
    eeveeTexture.loadFromFile("img/eevee_spritesheet.png");
    enemyTexture.loadFromFile("img/eevee_spritesheet.png"); //temp
    rectangle.setFillColor(sf::Color::Green);
    sf::Music music;
    music.openFromFile("./sfx/Music/route.wav");
    music.setLoop(true);
    music.setVolume(15);

    Eevee player(eeveeTexture);
    Enemy enemy(enemyTexture);
    Battle battle(&game, &player, &enemy);
    player.spritePosition(850, 510);
    //sf::Thread thread(&Battle::battle, &battle);
    //player.setCoords(227, 60, 60, 79);

    music.play();
    while (game.isOpen())
    {
        //Si un combat commence, on change d'écran
        //std::cout << "game fighting : " << game.getBattle() << std::endl;
        if (game.getBattle()) {
            std::cout << "BATTLE IS TRUE" << std::endl;
            std::cout << "----------" << std::endl << std::endl;
            music.stop();
            player.idle();
            game.setBattle(battle.battle());
            if (!battle.getChoice()) {
                std::cout << "NO CHOICE SELECTED" << std::endl;
                std::cout << "----------" << std::endl << std::endl;
                battle.setChoice(interface.battle() + 1);
                battle.turn();
                game.draw(player);
                game.display();
            }
            if (!game.getBattle()) {
                std::cout << "BATTLE ENDED" << std::endl;
                std::cout << "----------" << std::endl << std::endl;
                player.setCoords(0, 30, 27, 3);
                battle.reset();
            }
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
            
            game.clear();
            interface.map();
            interface.draw(rectangle);
            game.draw(player);
            game.display();
        }
    }

    return 0;
}