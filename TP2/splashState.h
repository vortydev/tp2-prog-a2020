/*
 * Author:		Étienne Ménard
 * Date:		18/12/2020
 * File:		splashState.h
 * Description:	Écran de démarrage du jeu.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "mainMenuState.h"
#include "splashSlime.h"

using namespace sf;
using namespace std;

class splashState : public state
{
private:
    gameDataRef _data;
    Clock _clock;
    Clock _textClock;

    Sprite _background;
    Text _loadingText;
    splashSlime* _slime;

public:
    splashState(gameDataRef data);
    ~splashState();

    void init();
    void handleInput();
    void update(float dt);
    void draw(float dt) const;
};

