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
    _confirmButton.enabled = true;
    _cancelButton.enabled = false;

    // loads confirm button sprite
    _confirmButton.buttonSprite.setTexture(_data->assets.getTexture("game menu button"));
    _confirmButton.buttonSprite.setPosition(SCREEN_WIDTH - 85 - _confirmButton.buttonSprite.getGlobalBounds().width, SCREEN_HEIGHT - _menuBody.getGlobalBounds().height - 40);

    // loads confirm button text
    _confirmButton.buttonText.setFont(_data->assets.getFont("game font"));
    _confirmButton.buttonText.setString("Wave");
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
}

// draws the menu and the buttons if they're enabled
void gameMenu::drawMenu() const
{
    _data->window.draw(_menuBody);

    if (_confirmButton.enabled) {
        _data->window.draw(_confirmButton.buttonSprite);
        _data->window.draw(_confirmButton.buttonText);
    }

    if (_cancelButton.enabled) {
        _data->window.draw(_cancelButton.buttonSprite);
        _data->window.draw(_cancelButton.buttonText);
    }
}

// toggles on and off buttons depending of the prep phase
void gameMenu::prepUpdate(int& prepPhase)
{
    if (prepPhase == prepPhases::unitSelection) {
        _confirmButton.enabled = true;
        _confirmButton.buttonText.setString("Wave");
        _confirmButton.buttonText.setPosition(SCREEN_WIDTH - 90 - _confirmButton.buttonSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT - 45 - _menuBody.getGlobalBounds().height + _confirmButton.buttonSprite.getGlobalBounds().height / 2);

        _cancelButton.enabled = false;
    }
    else if (prepPhase == prepPhases::unitPlacement) {
        _confirmButton.enabled = false;
        _cancelButton.enabled = true;
    }
    else if (prepPhase == prepPhases::unitTransaction) {
        _confirmButton.enabled = true;
        _confirmButton.buttonText.setString("Confirm");
        _confirmButton.buttonText.setPosition(SCREEN_WIDTH - 115 - _confirmButton.buttonSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT - 45 - _menuBody.getGlobalBounds().height + _confirmButton.buttonSprite.getGlobalBounds().height / 2);

        _cancelButton.enabled = true;
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

// retournes si le boutton est enabled
bool gameMenu::isConfirmButtonEnabled() const
{
    return _confirmButton.enabled;
}

// retournes si le boutton est enabled
bool gameMenu::isCancelButtonEnabled() const
{
    return _cancelButton.enabled;
}

// does different things depending of the prep phase
void gameMenu::clickConfirmButton(int& prepPhase, int& gameState)
{
    // si on est au début et on click sur Wave, on part la phase wave
    if (prepPhase == prepPhases::unitSelection) {
        prepPhase = prepPhases::hold;   // updates the prepPhase
        prepUpdate(prepPhase);         // updates buttons

        gameState = gameStates::wave;   // updates the gameState
    }
    // effectues la transaction de l'unit et reset la prep phase au début
    else if (prepPhase == prepPhases::unitTransaction) {
        prepPhase = prepPhases::unitSelection; //updates the prepPhase
        prepUpdate(prepPhase);                 // updates the buttons

        unitTransaction();                      // does the unit transaction
    }
}

// resets the prep phase to unitSelection
void gameMenu::clickCancelButton(int& prepPhase)
{
    prepPhase = prepPhases::unitSelection;  // updates the prepPhase
    prepUpdate(prepPhase);                 // updates the buttons
}

void gameMenu::unitTransaction() // TODO
{

}