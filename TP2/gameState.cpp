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
    _data->assets.loadTexture("game state background", GAME_BACKGROUND_FILEPATH);
    _background.setTexture(_data->assets.getTexture("game state background"));

    // load player zone
    _data->assets.loadTexture("player zone", GAME_PLAYER_ZONE_FILEPATH);
    _playerZone.setTexture(_data->assets.getTexture("player zone"));
    _playerZone.setPosition(75, 50);

    // load enemy zone
    _data->assets.loadTexture("enemy zone", GAME_ENEMY_ZONE_FILEPATH);
    _enemyZone.setTexture(_data->assets.getTexture("enemy zone"));
    _enemyZone.setPosition(SCREEN_WIDTH - _enemyZone.getGlobalBounds().width - 75, 50);

    // load menu body
    _data->assets.loadTexture("game menu body", GAME_MENU_BODY_FILEPATH);
    _menuBody.setTexture(_data->assets.getTexture("game menu body"));
    _menuBody.setPosition(75, SCREEN_HEIGHT - _menuBody.getGlobalBounds().height - 50);
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

    _data->window.draw(_background);
    _data->window.draw(_playerZone);
    _data->window.draw(_enemyZone);
    _data->window.draw(_menuBody);

    _data->window.display();
}