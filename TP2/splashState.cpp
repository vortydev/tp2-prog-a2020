/*
 * Author:		Étienne Ménard
 * Date:		18/12/2020
 * File:		splashState.cpp
 * Description:	Définitions des méthodes du splashState.
 */

#include "splashState.h"

splashState::splashState(gameDataRef data) : _data(data)
{

}

splashState::~splashState()
{
    delete _slime;
}

void splashState::init()
{
    // load bg
    _data->assets.loadTexture("splash bg", GAME_BACKGROUND_FILEPATH);
    _background.setTexture(_data->assets.getTexture("splash bg"));

    // load splash slime
    _slime = new splashSlime(_data);

    // load splashText
    _data->assets.loadFont("game font", GAME_FONT_FILEPATH);
    _loadingText.setFont(_data->assets.getFont("game font"));
    _loadingText.setString("Loading ");
    _loadingText.setCharacterSize(24);
    _loadingText.setFillColor(Color::White);
    _loadingText.setOrigin(_loadingText.getGlobalBounds().width / 2, _loadingText.getGlobalBounds().height / 2);
    _loadingText.setPosition(_data->window.getSize().x / 2 - 10, _data->window.getSize().y / 2 - _loadingText.getGlobalBounds().height / 2 + _slime->getSprite().getGlobalBounds().height);
}

void splashState::handleInput()
{
    Event event;
    while (_data->window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            _data->window.close();
    }
}

void splashState::update(float dt)
{
    _slime->animate(dt);

    if (_textClock.getElapsedTime().asSeconds() > 0.8) {
        _loadingText.setString(_loadingText.getString() + ".");
        _textClock.restart();
    }

    if (_clock.getElapsedTime().asSeconds() > 3.0)
    {
        //_data->machine.addState(stateRef(new mainMenuState(_data)), true);
        _data->machine.addState(stateRef(new gameState(_data)), true); // temp while main menu not done
    }
}

//clear, dessine le background et display la fenêtre. (dt n’est pas utilisé ici)
void splashState::draw(float dt) const
{
    _data->window.clear();

    _data->window.draw(_background);
    _data->window.draw(_loadingText);
    _slime->draw();

    _data->window.display();
}