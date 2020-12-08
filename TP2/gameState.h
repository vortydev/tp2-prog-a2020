/*
 * Author:		Étienne Ménard
 * Date:		29/11/2020
 * File:		gameState.h
 * Description:	Actual game being played.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"

#include "grid.h"

using namespace sf;
using namespace std;

//chaque state représentera une vraie fenêtre et hérite de state, car on implémentera
//un init, update, draw et handleInput différent pour chaque fenêtre.
class gameState : public state
{
private:
    gameDataRef _data;  //chaque state recevra le pointeur sur la gameData qui
                        //donne accès au stateMachine, au RenderWindow, au
                        //assertManager et au inputManager

    Clock _clock;

    int _gameState; // état du jeu
    int _score;     // score du joueur

    Sprite _background;
    Sprite _menuBody; //temp? might be it's own file
    Sprite _playerZone;
    Sprite _enemyZone;

    grid* _grid;    // pointeur sur la grid

public:
    gameState(gameDataRef data);
    ~gameState();

    void init();
    void handleInput();
    void update(float dt);
    void draw(float dt) const;
};