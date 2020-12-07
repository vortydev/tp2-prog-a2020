/*
 * Author:		Étienne Ménard
 * Date:		28/11/2020
 * File:		mainMenuState.h
 * Description:	Menu principal du jeu.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "gameState.h"
#include "state.hpp"
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

//chaque state représentera une vraie fenêtre et hérite de state, car on implémentera
//un init, update, draw et handleInput différent pour chaque fenêtre.
class mainMenuState : public state
{
private:
    gameDataRef _data;  //chaque state recevra le pointeur sur la gameData qui
                        //donne accès au stateMachine, au RenderWindow, au
                        //assertManager et au inputManager

public:
    mainMenuState(gameDataRef data);

    void init();
    void handleInput();
    void update(float dt);
    void draw(float dt) const;
};