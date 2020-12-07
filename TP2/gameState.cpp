/*
 * Author:		Étienne Ménard
 * Date:		29/11/2020
 * File:		gameState.cpp
 * Description:	Définitions des méthodes du gameState.
 */

#include "gameState.h"

 //le constructeur utilise les : pour initialiser _data avant même l’exécution du contenu{}
gameState::gameState(gameDataRef data) : _data(data)
{
    _score = 0;

    _gameState = gameStates::ready;
}

gameState::~gameState()
{

}

//load l’image du background à l’aide du assetManager ds _data et la set au Sprite
void gameState::init()
{
    // set le game state
    _gameState = gameStates::ready;

    // load bg sprite
    //_data->assets.loadTexture("game state background", MAIN_MENU_STATE_BACKGROUND_FILEPATH);
    //_background.setTexture(_data->assets.getTexture("game state background"));
}

//fenêtre qui reste ouverte tant qu’elle n’est pas fermée
void gameState::handleInput()
{
    Event event;
    while (_data->window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            _data->window.close();
    }
}

//gère le délai, après 3 secondes, on veut afficher la prochaine fenêtre
void gameState::update(float dt)
{
    
}

//clear, dessine le background et display la fenêtre. (dt n’est pas utilisé ici)
void gameState::draw(float dt) const
{
    _data->window.clear();

    //_data->window.draw(_background);

    _data->window.display();
}