/*
* Auteur : Pier-Alexandre Caron
* date de création : 2020-12-02
* projet : Flappy bird avec les games states
* nom du fichier : gameOverState.cpp
* but : Définition des méthodes de l'objet gameOverState
*/

#include "gameOverState.h"
#include "gameState.h"
#include <fstream>
#include <iostream>
#include <sstream>



//le constructeur utilise les : pour initialiser _data avant même l’exécution du contenu{}
gameOverState::gameOverState(gameDataRef data,int score) : _data(data), _score(score)
{
}
//load l’image du background à l’aide du assetManager ds _data et la set au Sprite
void gameOverState::init()
{
	_background.setTexture(_data->assets.getTexture("game state background"));
	
	// load play button sprite
	_data->assets.loadTexture("main menu button", MAIN_MENU_BUTTON_FILEPATH);
	_retryButton.buttonSprite.setTexture(_data->assets.getTexture("main menu button"));
	_retryButton.buttonSprite.setPosition(SCREEN_WIDTH / 2 - _retryButton.buttonSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - _retryButton.buttonSprite.getGlobalBounds().height / 2);
	// load play button text
	_retryButton.buttonText.setFont(_data->assets.getFont("game font"));
	_retryButton.buttonText.setString("Try Again");
	_retryButton.buttonText.setCharacterSize(48);
	_retryButton.buttonText.setFillColor(Color::White);
	_retryButton.buttonText.setOrigin(_retryButton.buttonText.getGlobalBounds().width / 2, _retryButton.buttonText.getGlobalBounds().height / 2);
	_retryButton.buttonText.setPosition(SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2);

	_gameOverTitle.setFont(_data->assets.getFont("game font"));
	_gameOverTitle.setString("Game Over");
	_gameOverTitle.setCharacterSize(96);
	_gameOverTitle.setFillColor(Color::Green);
	_gameOverTitle.setOrigin(_gameOverTitle.getGlobalBounds().width / 2, _gameOverTitle.getGlobalBounds().height / 2);
	_gameOverTitle.setPosition(SCREEN_WIDTH / 2, 150);

	_scoreText.setFont(_data->assets.getFont("game font"));
	_scoreText.setString("score : "+to_string(_score));
	_scoreText.setCharacterSize(50);
	_scoreText.setFillColor(Color::Green);
	_scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
	_scoreText.setPosition(SCREEN_WIDTH / 2, 225);

}
//fenêtre qui reste ouverte tant qu’elle n’est pas fermée
void gameOverState::handleInput()
{
	Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			_data->window.close();
		else if (_data->input.isSpriteClicked(_retryButton.buttonSprite, Mouse::Left, _data->window)) {
			//depile gameover et gamestate pour mettre un nouveau gameState
			_data->machine.removeState();
			_data->machine.addState(stateRef(new gameState(_data)), true);
			
		}
	}
}

void gameOverState::update(float dt)
{

}
//clear, dessine et display la fenêtre. (dt n’est pas utilisé ici)
void gameOverState::draw(float dt) const
{
	_data->window.clear();
	_data->window.draw(_background);
	_data->window.draw(_gameOverTitle);
	_data->window.draw(_retryButton.buttonSprite);
	_data->window.draw(_retryButton.buttonText);
	_data->window.draw(_scoreText);
	
	_data->window.display();
}