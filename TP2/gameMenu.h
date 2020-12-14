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

struct shopUnit {
    int cost;
    Text costText;
    Sprite unitCell;
    Sprite unitSprite;
};

class gameMenu
{
private:
    gameDataRef _data;

    bool _unitListEmpty;

    Sprite _menuBody;

    button _confirmButton;
    button _cancelButton;

    vecteur<shopUnit> _shopUnits;
    Sprite _tempUnit;

    cell _selectedCell;

public:
    gameMenu(gameDataRef data);

    void drawMenu()const;
    void drawButton(const button& b)const;
    //void drawShopUnits()const;

    button& getConfirmButton();
    button& getCancelButton();
    bool isButtonEnabled(const button& b)const;
    void toggleButton(button& b);

    void buttonVisibilityUpdate(int& prepPhase);
    void clickConfirmButton(int& prepPhase, int& gameState);
    void clickCancelButton(int& prepPhase);

    // unitSelection
    //Sprite& getTempUnit();
    //void unitSelected(int& prepPhase);

    //unitPlacement
    cell& getSelectedCell();

    //unitTransaction
    //void unitTransaction(); // TODO
};