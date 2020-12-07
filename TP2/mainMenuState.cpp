/*
 * Author:		Étienne Ménard
 * Date:		28/11/2020
 * File:		mainMenuState.cpp
 * Description:	Définitions des méthodes du mainMenuState.
 */

#include "mainMenuState.h"

 //le constructeur utilise les : pour initialiser _data avant même l’exécution du contenu{}
mainMenuState::mainMenuState(gameDataRef data) : _data(data)
{

}

//load l’image du background à l’aide du assetManager ds _data et la set au Sprite
void mainMenuState::init()
{
    
}

//fenêtre qui reste ouverte tant qu’elle n’est pas fermée
void mainMenuState::handleInput()
{
    Event event;
    while (_data->window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            _data->window.close();
    }
}

//gère le délai, après 3 secondes, on veut afficher la prochaine fenêtre
void mainMenuState::update(float dt)
{

}

//clear, dessine le background et display la fenêtre. (dt n’est pas utilisé ici)
void mainMenuState::draw(float dt) const
{
    _data->window.clear();

    _data->window.display();
}