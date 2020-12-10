/*
 * Author:		Étienne Ménard
 * Date:		09/12/2020
 * File:		gameMenu.h
 * Description:	Menu utilisé durant la phase prep pour acheter et positionner les units
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "grid.h"
#include "Resources/include/vecteur.hpp"

using namespace sf;

struct button {
    Sprite buttonSprite;
    Text buttonText;
    bool enabled;
};

class gameMenu
{
private:
    gameDataRef _data;

    // vecteur des units à implémenter

    Sprite _menuBody;
    Sprite _tempUnit;

    button _confirmButton;
    button _cancelButton;

    cell _selectedCell;

public:
    gameMenu(gameDataRef data);
    void drawMenu()const;
    void prepUpdate(int& prepPhase);

    button& getConfirmButton();
    button& getCancelButton();
    bool isConfirmButtonEnabled()const;
    bool isCancelButtonEnabled()const;
    void toggleButton(button& b);

    void clickWaveButton(int& prepPhase, int& gameState);
    void clickConfirmButton(int& prepPhase);
    void clickCancelButton(int& prepPhase);

    // unitSelection
    Sprite& getTempUnit();
    void unitSelected();

    //unitPlacement
    cell& getSelectedCell();
    void cellSelected(cell& c);

    //unitTransaction
    //void unitTransaction(); // TODO
};