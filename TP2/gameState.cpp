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
    
    delete _actionGuide;
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

    // load currency text
    _currencyText.setFont(_data->assets.getFont("game font"));
    _currencyText.setString(to_string(_currency));
    _currencyText.setCharacterSize(36);
    _currencyText.setFillColor(Color::Yellow);
    _currencyText.setOrigin(_currencyText.getGlobalBounds().width / 2, _currencyText.getGlobalBounds().height / 2);
    _currencyText.setPosition(75 + _playerZone.getGlobalBounds().width / 2, 75);

    // load coin sprite
    _data->assets.loadTexture("coin", GAME_CURRENCY_FILEPATH);
    _coin.setTexture(_data->assets.getTexture("coin"));
    _coin.setPosition(70, 85 - _coin.getGlobalBounds().height / 2);

    // load grid
    _data->assets.loadTexture("grid cell empty", GRID_CELL_EMPTY_FILEPATH);
    _data->assets.loadTexture("grid cell white", GRID_CELL_WHITE_FILEPATH);
    _data->assets.loadTexture("grid cell grey", GRID_CELL_GREY_FILEPATH);
    _data->assets.loadTexture("grid cell pink", GRID_CELL_PINK_FILEPATH);
    _data->assets.loadTexture("grid cell red", GRID_CELL_RED_FILEPATH);
    _data->assets.loadTexture("grid cell blood", GRID_CELL_BLOOD_FILEPATH);
    _data->assets.loadTexture("grid cell yellow", GRID_CELL_YELLOW_FILEPATH);
    _data->assets.loadTexture("grid cell mustard", GRID_CELL_MUSTARD_FILEPATH);
    _data->assets.loadTexture("grid cell green", GRID_CELL_GREEN_FILEPATH);
    _data->assets.loadTexture("grid cell blue", GRID_CELL_BLUE_FILEPATH);
    _grid = new grid(_data);

    // load game menu
    _data->assets.loadTexture("game menu body", GAME_MENU_BODY_FILEPATH);
    _data->assets.loadTexture("game menu button", GAME_MENU_BUTTON_FILEPATH);
    _menu = new gameMenu(_data);

    // load the entity manager
    _entityManager = new entityManager(_data);


    // load le actionGuide
    _data->assets.loadTexture("action cell off", GAME_ACTION_CELL_OFF);
    _data->assets.loadTexture("action cell on", GAME_ACTION_CELL_ON);
    _data->assets.loadTexture("action instruction", GAME_ACTION_INSTRUCTION);
    _actionGuide = new actionGuide(_data);

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
        // click Help button
        else if (_gameState == gameStates::prep && _data->input.isSpriteClicked(_actionGuide->getHelpSprite(), Mouse::Left, _data->window)) {
            _actionGuide->toggleHelp();
        }
        // click Cancel button
        else if (_gameState == gameStates::prep && _menu->isButtonEnabled(_menu->getCancelButton()) && _data->input.isSpriteClicked(_menu->getCancelButton().buttonSprite, Mouse::Left, _data->window)) {
            // if a unit was selected
            if (_menu->isUnitSelected())
                _entityManager->unSelectCell(_menu->getSelectedUnit());
            
            // if a cell was selected
            if (_menu->isPlacementSelected())
                _grid->unSelectCell(_menu->getSelectedPlacement());

            _menu->clickCancelButton(_prepPhase, _entityManager->boardEntitiesSize());
        }
        // click Confirm button
        else if (_gameState == gameStates::prep && _menu->isButtonEnabled(_menu->getConfirmButton()) && _data->input.isSpriteClicked(_menu->getConfirmButton().buttonSprite, Mouse::Left, _data->window)) {
            if (_prepPhase == prepPhases::unitSelling) {
                _entityManager->sellUnit(_menu->getSelectedPlacement(), _currency);
                _currencyText.setString(to_string(_currency));

                _grid->setOccupied(_menu->getSelectedPlacement().cellX, _menu->getSelectedPlacement().cellY);
                _grid->unSelectCell(_menu->getSelectedPlacement());
                
            }

            _menu->clickConfirmButton(_prepPhase, _gameState);

            if (_prepPhase == prepPhases::unitTransaction) {
                // soustrait le cout de l'unit de la currency et update le text
                _entityManager->buyUnit(_menu->getSelectedUnit(), _currency);
                _currencyText.setString(to_string(_currency));

                // ajoutes une copie de l'unit dans la liste d'entitées sur le board
                _entityManager->addUnitToBoard(_menu->getSelectedUnit(), _menu->getSelectedPlacement());

                // déselectionne la shop unit cell
                _entityManager->unSelectCell(_menu->getSelectedUnit());

                // set la cell sélectionnée as occupied et la déselectionne
                _grid->setOccupied(_menu->getSelectedPlacement().cellX, _menu->getSelectedPlacement().cellY);
                _grid->unSelectCell(_menu->getSelectedPlacement());

                _prepPhase = prepPhases::awaitingWave;      //updates the prepPhase
            }
            else if (_prepPhase == hold) {
                _grid->toggleGrid();
                _actionGuide->untoggleHelp();
                _gameState = gameStates::wave;
                //spawn slime here
            }

            _menu->buttonVisibilityUpdate(_prepPhase);  // updates the buttons
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
        // Select cell on grid
        else if (_gameState == gameStates::prep && _data->input.isSpriteClicked(_grid->getCell(_data).sprite, Mouse::Left, _data->window)) {
            // prep::unitPlacement
            if (_menu->isUnitSelected()) {
                // set la prepPhase à unitPlacement
                if (_prepPhase != prepPhases::unitPlacement) {
                    _prepPhase = prepPhases::unitPlacement;
                    _menu->buttonVisibilityUpdate(_prepPhase);
                }

                cell tempCell = _grid->getCell(_data);
                if (!_grid->isOccupied(tempCell)) {
                    _grid->setSelectColor(selectColor::blue);
                    _grid->setSelected(tempCell.cellX, tempCell.cellY, _menu->getSelectedPlacement());
                }
            }
            // prep::unitSelling
            else {
                cell tempCell = _grid->getCell(_data);
                if (_grid->isOccupied(tempCell) && !(!_entityManager->isBoardUnitOnCell(tempCell) || _entityManager->isBoardMobOnCell(tempCell))) {
                    if (_prepPhase != prepPhases::unitSelling) {
                        _prepPhase = prepPhases::unitSelling;
                        _menu->buttonVisibilityUpdate(_prepPhase);
                    }

                    if (_entityManager->getBoardEntity(tempCell).isNew())
                        _grid->setSelectColor(selectColor::yellow);
                    else
                        _grid->setSelectColor(selectColor::mustard);

                    _grid->setSelected(tempCell.cellX, tempCell.cellY, _menu->getSelectedPlacement());
                }
            }
        }
        
        
        _actionGuide->updateInstructionsShown(_prepPhase, _menu->isButtonEnabled(_menu->getConfirmButton()), _menu->isButtonEnabled(_menu->getCancelButton()), _menu->isUnitSelected(), _menu->isPlacementSelected(), _entityManager->boardEntitiesSize(), _currency);
    }
}

// core update loop
void gameState::update(float dt)
{
    
    if (_gameState == gameStates::wave) {
        
        if (_clock.getElapsedTime().asSeconds() > BEHAVIOR_CLOCK) {
            //_entityManager->processEntityBehavior();

            _clock.restart();
        }
        _entityManager->update(dt);
        
    }
}

//clear, dessine le background et display la fenêtre. (dt n’est pas utilisé ici)
void gameState::draw(float dt) const
{
    
    _data->window.clear();

    _data->window.draw(_background);
    _data->window.draw(_playerZone);
    _data->window.draw(_enemyZone);

    // currency
    _data->window.draw(_coin);
    _data->window.draw(_currencyText);

    // board
    _grid->drawGrid();
    _entityManager->drawBoardEntities();

    // shop
    _menu->drawMenu();
    _entityManager->drawShopUnits(_currency);

    // help
    _actionGuide->draw();

    _data->window.display();
}