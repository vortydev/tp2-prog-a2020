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
#include "gameMenu.h"
#include "entityManager.h"
#include "waveManager.h"

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
    int _prepPhase; // état de la phase prep

    int _score;     // score du joueur
    int _currency;  // currency du joueur

    Sprite _background;
    Sprite _playerZone;
    Sprite _enemyZone;

    Sprite _coin;
    Text _currencyText;

    grid* _grid;        // pointeur sur la grid
    gameMenu* _menu;    // pointeur sur le menu
    entityManager* _entityManager;
    waveManager* _waveManager;

public:
    gameState(gameDataRef data);
    ~gameState();

    void init();
    void handleInput();
    void update(float dt);
    void draw(float dt) const;
};