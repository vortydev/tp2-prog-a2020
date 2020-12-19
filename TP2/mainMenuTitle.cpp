/*
 * Author:		Étienne Ménard
 * Date:		18/12/2020
 * File:		mainMenuTitle.cpp
 * Description:	Définitions des méthodes du mainMenuTitle.
 */

#include "mainMenuTitle.h"

mainMenuTitle::mainMenuTitle(gameDataRef data) : _data(data)
{
    _titleDelay = false;
    
    _title.setFont(_data->assets.getFont("game font"));
    _title.setString("Slimey Chess");
    _title.setCharacterSize(96);
    _title.setFillColor(Color::Green);
    _title.setOrigin(_title.getGlobalBounds().width / 2, _title.getGlobalBounds().height / 2);
    _title.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    _titleShadow.setFont(_data->assets.getFont("game font"));
    _titleShadow.setString("Slimey Chess");
    _titleShadow.setCharacterSize(96);
    _titleShadow.setFillColor(Color::Black);
    _titleShadow.setOrigin(_title.getGlobalBounds().width / 2, _title.getGlobalBounds().height / 2);
    _titleShadow.setPosition(SCREEN_WIDTH / 2 + 5, SCREEN_HEIGHT / 2 + 5);
}

void mainMenuTitle::draw() const
{
    _data->window.draw(_titleShadow);
    _data->window.draw(_title);
}

void mainMenuTitle::animate(float dt)
{
    if (!_titleDelay && _clock.getElapsedTime().asSeconds() > TITLE_ANIMATION_DELAY)
    {
        _titleDelay = true;
        _clock.restart();
    }

    if (_titleDelay && _clock.getElapsedTime().asSeconds() < TITLE_ANIMATION_DURATION) {
        _title.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - _clock.getElapsedTime().asMilliseconds() / 14);
        _titleShadow.setPosition(SCREEN_WIDTH / 2 + 5, SCREEN_HEIGHT / 2 + 5 - _clock.getElapsedTime().asMilliseconds() / 14);
    }
}