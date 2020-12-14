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
    _gameState = gameStates::loading;
    _prepPhase = prepPhases::hold;

    _score = 0;
    _currency = 100;
}

gameState::~gameState()
{
    delete _grid;
    delete _menu;
    delete _entityManager;
}

void gameState::init()
{
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

    // load grid
    _data->assets.loadTexture("grid cell empty", GRID_CELL_EMPTY_FILEPATH);
    _data->assets.loadTexture("grid cell white", GRID_CELL_WHITE_FILEPATH);
    _data->assets.loadTexture("grid cell grey", GRID_CELL_GREY_FILEPATH);
    _data->assets.loadTexture("grid cell red", GRID_CELL_RED_FILEPATH);
    _data->assets.loadTexture("grid cell green", GRID_CELL_GREEN_FILEPATH);
    _data->assets.loadTexture("grid cell blue", GRID_CELL_BLUE_FILEPATH);
    _grid = new grid(_data);

    // load game menu
    _data->assets.loadFont("game font", GAME_FONT_FILEPATH);
    _data->assets.loadTexture("game menu body", GAME_MENU_BODY_FILEPATH);
    _data->assets.loadTexture("game menu button", GAME_MENU_BUTTON_FILEPATH);
    _menu = new gameMenu(_data);

    // load the entity manager
    _entityManager = new entityManager(_data);

    // set le game state et prepPhase
    _gameState = gameStates::prep;
    _prepPhase = prepPhases::unitSelection;
}

// handles all user input
void gameState::handleInput()
{
    Event event;
    while (_data->window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            _data->window.close();
        // click Cancel button
        else if (_gameState == gameStates::prep && _menu->isButtonEnabled(_menu->getCancelButton()) && _data->input.isSpriteClicked(_menu->getCancelButton().buttonSprite, Mouse::Left, _data->window)) {
            // if a unit was selected
            if (_prepPhase >= prepPhases::unitSelection)
                _entityManager->unSelectCell(_menu->getSelectedUnit());
            
            // if a cell was selected
            if (_prepPhase >= prepPhases::unitPlacement)
                _grid->unSelectCell(_menu->getSelectedCell());

            _menu->clickCancelButton(_prepPhase, _entityManager->boardEntitiesSize());
        }
        // click Confirm button
        else if (_gameState == gameStates::prep && _menu->isButtonEnabled(_menu->getConfirmButton()) && _data->input.isSpriteClicked(_menu->getConfirmButton().buttonSprite, Mouse::Left, _data->window)) {
            _menu->clickConfirmButton(_prepPhase, _gameState);

            if (_prepPhase == prepPhases::unitTransaction) {
                _entityManager->addUnitToBoard(_menu->getSelectedUnit(), _menu->getSelectedCell());
                _entityManager->unitTransaction(_menu->getSelectedUnit(), _currency);

                _prepPhase = prepPhases::awaitingWave;      //updates the prepPhase
                _menu->buttonVisibilityUpdate(_prepPhase);  // updates the buttons

                _entityManager->unSelectCell(_menu->getSelectedUnit());

                _grid->setOccupied(_menu->getSelectedCell().cellX, _menu->getSelectedCell().cellY);
                _grid->unSelectCell(_menu->getSelectedCell());

                _menu->toggleButton(_menu->getCancelButton());
            }
            else if (_prepPhase == hold)
                _grid->toggleGrid();
        }
        // prep::unitSelection. Select an a affordable unit
        else if ((_prepPhase == prepPhases::unitSelection || _prepPhase == prepPhases::awaitingWave) && _data->input.isSpriteClicked(_entityManager->getShopUnitCell(_data).sprite, Mouse::Left, _data->window)) {
            if (_prepPhase != prepPhases::unitSelection) {
                _prepPhase = prepPhases::unitSelection;
                _menu->buttonVisibilityUpdate(_prepPhase);
            }
            
            cell tempUnit = _entityManager->getShopUnitCell(_data);
            _entityManager->setSelected(tempUnit.cellX, _menu->getSelectedUnit());
        }
        // prep::unitPlacement. Select cell on grid
        else if ((_prepPhase == prepPhases::unitSelection || _prepPhase == prepPhases::unitPlacement) && _data->input.isSpriteClicked(_grid->getCell(_data).sprite, Mouse::Left, _data->window)) {
            if (_prepPhase != prepPhases::unitPlacement)
                _prepPhase = prepPhases::unitPlacement;
            
            cell tempCell = _grid->getCell(_data);
            if (!_grid->isOccupied(tempCell))
                _grid->setSelected(tempCell.cellX, tempCell.cellY, _menu->getSelectedCell());
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

    _grid->drawGrid();
    _menu->drawMenu();
    _entityManager->drawShopUnits(_currency);
    _entityManager->drawBoardEntities();

    _data->window.display();
}