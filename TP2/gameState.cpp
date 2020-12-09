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
    delete _grid;
}

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

    // load grid
    _data->assets.loadTexture("grid cell empty", GRID_CELL_EMPTY_FILEPATH);
    _data->assets.loadTexture("grid cell white", GRID_CELL_WHITE_FILEPATH);
    _data->assets.loadTexture("grid cell grey", GRID_CELL_GREY_FILEPATH);
    _data->assets.loadTexture("grid cell red", GRID_CELL_RED_FILEPATH);
    _data->assets.loadTexture("grid cell green", GRID_CELL_GREEN_FILEPATH);
    _data->assets.loadTexture("grid cell blue", GRID_CELL_BLUE_FILEPATH);
    _grid = new grid(_data);
}

//fenêtre qui reste ouverte tant qu’elle n’est pas fermée
void gameState::handleInput()
{
    Event event;
    while (_data->window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            _data->window.close();
        else if (_data->input.isSpriteClicked(_grid->getCell(_data).sprite, Mouse::Left, _data->window)) {
            cell selectedCell = _grid->getCell(_data);
            _grid->setOccupied(selectedCell.cellX, selectedCell.cellY); // temp
        }
        else if (_data->input.isSpriteClicked(_background, Mouse::Left, _data->window)) {
            _grid->toggleGrid(); // temp
        }
    }
}

// core update loop
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

    _grid->drawGrid();

    _data->window.display();
}