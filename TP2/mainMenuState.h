/*
 * Author:		Étienne Ménard
 * Date:		28/11/2020
 * File:		mainMenuState.h
 * Description:	Menu principal du jeu.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "gameState.h"
#include "mainMenuTitle.h"

using namespace sf;
using namespace std;

//chaque state représentera une vraie fenêtre et hérite de state, car on implémentera
//un init, update, draw et handleInput différent pour chaque fenêtre.
class mainMenuState : public state
{
private:
    gameDataRef _data;
    Clock _clock;

    Sprite _background;

    mainMenuTitle* _title;

    bool _buttonDelay;
    button _playButton;
    button _creditButton;

    bool _creditsShown;
    Text _credits;

public:
    mainMenuState(gameDataRef data);
    ~mainMenuState();

    void init();
    void handleInput();
    void update(float dt);
    void draw(float dt) const;
};