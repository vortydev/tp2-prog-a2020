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

    button _confirmButton;
    button _cancelButton;

public:
    gameMenu(gameDataRef data);
    void drawMenu()const;
    void prepUpdate(int& prepPhase);

    button& getConfirmButton();
    button& getCancelButton();
    bool isConfirmButtonEnabled()const;
    bool isCancelButtonEnabled()const;

    void clickConfirmButton(int& prepPhase, int& gameState);
    void clickCancelButton(int& prepPhase);

    void unitTransaction(); // TODO
};

