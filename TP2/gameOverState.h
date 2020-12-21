/*
* Auteur : Pier-Alexandre Caron
* date de cr�ation : 2020-12-20
* projet : slimey chess
* nom du fichier : gameOverState.h
* but : D�claration des m�thodes de l'objet gameOverState
*/
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "state.hpp"
#include "gameMenu.h"

//#include "mainMenuState.hpp"
using namespace sf;
using namespace std;

//chaque state repr�sentera une vraie fen�tre et h�rite de state, car on impl�mentera
//un init, update, draw et handleInput diff�rent pour chaque fen�tre.
class gameOverState : public state
{
private:
	gameDataRef _data; //chaque state recevra le pointeur sur la gameData qui
	//donne acc�s au stateMachine, au RenderWindow, au
	//assertManager et au inputManager

	Sprite _background; //le sprite pour la background

	Text _gameOverTitle;

	button _retryButton;

	Text _scoreText;
	
	int _score;

public:
	gameOverState(gameDataRef data,int score);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt) const;
};



