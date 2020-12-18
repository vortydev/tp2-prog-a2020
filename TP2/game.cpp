/*
 * Author:		�tienne M�nard
 * Date:		26/11/2020
 * File:		game.cpp
 * Description:	D�f�nition des m�thodes de la game.
 */

#include "game.h"
#include "splashState.h"

game::game(int width, int height, string title)
{
    srand(time(0));

    _data = make_shared<gameData>(); //cr�ation de la game en m�moire dynamique
    //cr�ation de la fen�tre qui changera de contenu selon la state cr��e ensuite
    _data->window.create(VideoMode(width, height), title, Style::Close | Style::Titlebar);

    _data->machine.addState(stateRef(new splashState(_data)));

    run();
}

//le game loop de tout jeu fonctionne comme suit : on ex�cute � chaque loop la m�thode
//processStateChanges qui v�rifie si on ajoute, on modifie ou on retire une state pour ensuite
//ajuster le temps pass� et ex�cuter des traitements particuliers � chaque (1/60sec)
//ces traitements sont g�rer par la state machine. Ensuite, on dessine les changements
void game::run()
{
    float newTime, frameTime, interpolation;
    float currentTime = _clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (_data->window.isOpen())
    {
        _data->machine.processStateChanges(); //v�rifie si on a des changements

        newTime = _clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if (frameTime > 0.25f) {    //si on d�passe le quart de seconde, on ajuste
            frameTime = 0.25f;      //a .25 seconde pour le calcul de accumulator
        }

        currentTime = newTime;      //new time devient le current time
        accumulator += frameTime;   //accumulator accumule tous les frameTimes

        while (accumulator >= dt) { //si on d�passe le temps du frame (1/60 de seconde)
                                    //on v�rifie les �v�nements et on update la fen�tre
            _data->machine.getActiveState()->handleInput();
            _data->machine.getActiveState()->update(dt);
            accumulator -= dt; //on retire dt de l'accumulateur pour l�interpolation
        }

        interpolation = accumulator / dt; //le temps d�ex�cution de la loop pour le draw
        _data->machine.getActiveState()->draw(interpolation);
    }
}