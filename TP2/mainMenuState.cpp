/*
 * Author:		�tienne M�nard
 * Date:		28/11/2020
 * File:		mainMenuState.cpp
 * Description:	D�finitions des m�thodes du mainMenuState.
 */

#include "mainMenuState.h"

 //le constructeur utilise les : pour initialiser _data avant m�me l�ex�cution du contenu{}
mainMenuState::mainMenuState(gameDataRef data) : _data(data)
{

}

//load l�image du background � l�aide du assetManager ds _data et la set au Sprite
void mainMenuState::init()
{
    
}

//fen�tre qui reste ouverte tant qu�elle n�est pas ferm�e
void mainMenuState::handleInput()
{
    Event event;
    while (_data->window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            _data->window.close();
    }
}

//g�re le d�lai, apr�s 3 secondes, on veut afficher la prochaine fen�tre
void mainMenuState::update(float dt)
{

}

//clear, dessine le background et display la fen�tre. (dt n�est pas utilis� ici)
void mainMenuState::draw(float dt) const
{
    _data->window.clear();

    _data->window.display();
}