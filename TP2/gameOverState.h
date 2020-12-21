/*
* Auteur : Pier-Alexandre Caron
* date de création : 2020-12-20
* projet : slimey chess
* nom du fichier : gameOverState.h
* but : Déclaration des méthodes de l'objet gameOverState
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

//chaque state représentera une vraie fenêtre et hérite de state, car on implémentera
//un init, update, draw et handleInput différent pour chaque fenêtre.
class gameOverState : public state
{
private:
	gameDataRef _data; //chaque state recevra le pointeur sur la gameData qui
	//donne accès au stateMachine, au RenderWindow, au
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



