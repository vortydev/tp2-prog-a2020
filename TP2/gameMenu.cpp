/*
 * Author:		Étienne Ménard
 * Date:		09/12/2020
 * File:		gameMenu.cpp
 * Description:	Définitions des méthodes de gameMenu.
 */

#include "gameMenu.h"

gameMenu::gameMenu(gameDataRef data) : _data(data)
{
    // loads menu body
    _menuBody.setTexture(_data->assets.getTexture("game menu body"));
    _menuBody.setPosition(75, SCREEN_HEIGHT - _menuBody.getGlobalBounds().height - 50);

    // sets buttons to their initial state
    _confirmButton.enabled = false;
    _cancelButton.enabled = false;

    // loads confirm button sprite
    _confirmButton.buttonSprite.setTexture(_data->assets.getTexture("game menu button"));
    _confirmButton.buttonSprite.setPosition(SCREEN_WIDTH - 85 - _confirmButton.buttonSprite.getGlobalBounds().width, SCREEN_HEIGHT - _menuBody.getGlobalBounds().height - 40);

    // loads confirm button text
    _confirmButton.buttonText.setFont(_data->assets.getFont("game font"));
    _confirmButton.buttonText.setString("Confirm");
    _confirmButton.buttonText.setCharacterSize(42);
    _confirmButton.buttonText.setFillColor(Color::White);
    _confirmButton.buttonText.setOrigin(_confirmButton.buttonText.getGlobalBounds().width / 2, _confirmButton.buttonText.getGlobalBounds().height / 2);
    _confirmButton.buttonText.setPosition(SCREEN_WIDTH - 90 - _confirmButton.buttonSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT - 45 - _menuBody.getGlobalBounds().height + _confirmButton.buttonSprite.getGlobalBounds().height / 2);

    // loads cancel button sprite
    _cancelButton.buttonSprite.setTexture(_data->assets.getTexture("game menu button"));
    _cancelButton.buttonSprite.setPosition(SCREEN_WIDTH - 85 - _cancelButton.buttonSprite.getGlobalBounds().width, SCREEN_HEIGHT - 60 - _cancelButton.buttonSprite.getGlobalBounds().height);

    // loads confirm button text
    _cancelButton.buttonText.setFont(_data->assets.getFont("game font"));
    _cancelButton.buttonText.setString("Cancel");
    _cancelButton.buttonText.setCharacterSize(42);
    _cancelButton.buttonText.setFillColor(Color::White);
    _cancelButton.buttonText.setOrigin(_cancelButton.buttonText.getGlobalBounds().width / 2, _cancelButton.buttonText.getGlobalBounds().height / 2);
    _cancelButton.buttonText.setPosition(SCREEN_WIDTH - 90 - _cancelButton.buttonSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT - 65 - _cancelButton.buttonSprite.getGlobalBounds().height / 2);

    // load temp unit
    _tempUnit.setTexture(_data->assets.getTexture("grid cell grey"));
    _tempUnit.setPosition(85, SCREEN_HEIGHT - _menuBody.getGlobalBounds().height - _tempUnit.getGlobalBounds().height / 2);

    // load selectedCell
    _selectedCell.cellX = -1;
    _selectedCell.selected = false;
}

// draws the menu and the buttons if they're enabled
void gameMenu::drawMenu() const
{
    _data->window.draw(_menuBody);

    drawButton(_confirmButton);
    drawButton(_cancelButton);

    _data->window.draw(_tempUnit);
}

// draw le bouton entré en paramètre si il est enabled
void gameMenu::drawButton(const button& b) const
{
    if (b.enabled) {
        _data->window.draw(b.buttonSprite);
        _data->window.draw(b.buttonText);
    }
}

// toggles on and off buttons depending of the prep phase
void gameMenu::prepPhaseUpdate(int& prepPhase)
{
    if (prepPhase == prepPhases::unitSelection) {
        _confirmButton.enabled = false;
        _confirmButton.buttonText.setString("Confirm");
        _confirmButton.buttonText.setPosition(SCREEN_WIDTH - 90 - _confirmButton.buttonSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT - 45 - _menuBody.getGlobalBounds().height + _confirmButton.buttonSprite.getGlobalBounds().height / 2);

        _cancelButton.enabled = false;
    }
    else if (prepPhase == prepPhases::unitPlacement) {
        _confirmButton.enabled = false;
        _cancelButton.enabled = true;
    }
    else if (prepPhase == prepPhases::awaitingWave) {
        _confirmButton.enabled = true;
        _confirmButton.buttonText.setString("Wave");
        _confirmButton.buttonText.setPosition(SCREEN_WIDTH - 90 - _confirmButton.buttonSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT - 45 - _menuBody.getGlobalBounds().height + _confirmButton.buttonSprite.getGlobalBounds().height / 2);
    
        _cancelButton.enabled = false;
    }
    else if (prepPhase == prepPhases::hold) {
        _confirmButton.enabled = false;
        _cancelButton.enabled = false;
    }
}

// retournes le bouton confirm
button& gameMenu::getConfirmButton()
{
    return _confirmButton;
}

// retournes le button cancel
button& gameMenu::getCancelButton()
{
    return _cancelButton;
}

// retournes si le bouton est enabled
bool gameMenu::isButtonEnabled(const button& b) const
{
    return b.enabled;
}

void gameMenu::toggleButton(button& b)
{
    b.enabled = !b.enabled;
}

// when the wave button is clicked
void gameMenu::clickWaveButton(int& prepPhase, int& gameState)
{
    prepPhase = prepPhases::hold;   // updates the prepPhase
    prepPhaseUpdate(prepPhase);     // updates buttons

    gameState = gameStates::wave;   // updates the gameState
}

// when the confirm button is clicked
void gameMenu::clickConfirmButton(int& prepPhase)
{
    if (prepPhase == prepPhases::unitSelection) {
        prepPhase = prepPhases::unitPlacement;
        prepPhaseUpdate(prepPhase);
    }
    else if (prepPhase == prepPhases::unitPlacement) {
        prepPhase = prepPhases::unitTransaction;
        //unitTransaction();    // does the unit transaction (might get it's own file)

        prepPhase = prepPhases::awaitingWave;   //updates the prepPhase
        prepPhaseUpdate(prepPhase);                  // updates the buttons
    }
}

// resets the prep phase to unitSelection
void gameMenu::clickCancelButton(int& prepPhase)
{
    // if a unit was selected
    if (prepPhase >= prepPhases::unitSelection)
        _tempUnit.setTexture(_data->assets.getTexture("grid cell grey"));

    // if the list of board units is empty
    prepPhase = prepPhases::unitSelection;  // updates the prepPhase
    // else 
    // prepPhase = prepPhases::awaitWave;

    prepPhaseUpdate(prepPhase);             // updates the buttons
}

Sprite& gameMenu::getTempUnit()
{
    return _tempUnit;
}

void gameMenu::unitSelected()
{
    _tempUnit.setTexture(_data->assets.getTexture("grid cell green"));

    if (!isButtonEnabled(getConfirmButton()))
        toggleButton(_confirmButton);

    if (!isButtonEnabled(getCancelButton()))
        toggleButton(_cancelButton);
}

cell& gameMenu::getSelectedCell()
{
    return _selectedCell;
}

void gameMenu::cellSelected(cell& c)
{
    _selectedCell.cellX = c.cellX;
    _selectedCell.cellY = c.cellY;

    if (!isButtonEnabled(_confirmButton))
        toggleButton(_confirmButton);
}