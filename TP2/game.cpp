/*
 * Author:		Étienne Ménard
 * Date:		26/11/2020
 * File:		game.cpp
 * Description:	Défénition des méthodes de la game.
 */

#include "game.h"
#include "splashState.h"

game::game(int width, int height, string title)
{
    srand(time(0));

    _data = make_shared<gameData>(); //création de la game en mémoire dynamique
    //création de la fenêtre qui changera de contenu selon la state créée ensuite
    _data->window.create(VideoMode(width, height), title, Style::Close | Style::Titlebar);

    _data->machine.addState(stateRef(new splashState(_data)));

    run();
}

//le game loop de tout jeu fonctionne comme suit : on exécute à chaque loop la méthode
//processStateChanges qui vérifie si on ajoute, on modifie ou on retire une state pour ensuite
//ajuster le temps passé et exécuter des traitements particuliers à chaque (1/60sec)
//ces traitements sont gérer par la state machine. Ensuite, on dessine les changements
void game::run()
{
    float newTime, frameTime, interpolation;
    float currentTime = _clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (_data->window.isOpen())
    {
        _data->machine.processStateChanges(); //vérifie si on a des changements

        newTime = _clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if (frameTime > 0.25f) {    //si on dépasse le quart de seconde, on ajuste
            frameTime = 0.25f;      //a .25 seconde pour le calcul de accumulator
        }

        currentTime = newTime;      //new time devient le current time
        accumulator += frameTime;   //accumulator accumule tous les frameTimes

        while (accumulator >= dt) { //si on dépasse le temps du frame (1/60 de seconde)
                                    //on vérifie les événements et on update la fenêtre
            _data->machine.getActiveState()->handleInput();
            _data->machine.getActiveState()->update(dt);
            accumulator -= dt; //on retire dt de l'accumulateur pour l’interpolation
        }

        interpolation = accumulator / dt; //le temps d’exécution de la loop pour le draw
        _data->machine.getActiveState()->draw(interpolation);
    }
}