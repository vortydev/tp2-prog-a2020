/*
 * Author:		Étienne Ménard
 * Date:		28/11/2020
 * File:		mainMenuState.cpp
 * Description:	Définitions des méthodes du mainMenuState.
 */

#include "mainMenuState.h"

mainMenuState::mainMenuState(gameDataRef data) : _data(data)
{
    _buttonDelay = false;
    _creditsShown = false;
}

mainMenuState::~mainMenuState()
{
    delete _title;
}

void mainMenuState::init()
{
    // load bg
    _data->assets.loadTexture("main menu background", GAME_BACKGROUND_FILEPATH);
    _background.setTexture(_data->assets.getTexture("main menu background"));

    // load title
    _title = new mainMenuTitle(_data);

    // load play button sprite
    _data->assets.loadTexture("main menu button", MAIN_MENU_BUTTON_FILEPATH);
    _playButton.buttonSprite.setTexture(_data->assets.getTexture("main menu button"));
    _playButton.buttonSprite.setPosition(SCREEN_WIDTH / 2 - _playButton.buttonSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - _playButton.buttonSprite.getGlobalBounds().height / 2);
    // load play button text
    _playButton.buttonText.setFont(_data->assets.getFont("game font"));
    _playButton.buttonText.setString("Play");
    _playButton.buttonText.setCharacterSize(48);
    _playButton.buttonText.setFillColor(Color::White);
    _playButton.buttonText.setOrigin(_playButton.buttonText.getGlobalBounds().width / 2, _playButton.buttonText.getGlobalBounds().height / 2);
    _playButton.buttonText.setPosition(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 2);

    // load credits button sprite
    _creditButton.buttonSprite.setTexture(_data->assets.getTexture("main menu button"));
    _creditButton.buttonSprite.setPosition(SCREEN_WIDTH / 2 - _creditButton.buttonSprite.getGlobalBounds().width / 2,
        SCREEN_HEIGHT / 2 - _creditButton.buttonSprite.getGlobalBounds().height / 2 + _playButton.buttonSprite.getGlobalBounds().height + 15);
    // load credits button text
    _creditButton.buttonText.setFont(_data->assets.getFont("game font"));
    _creditButton.buttonText.setString("Credits");
    _creditButton.buttonText.setCharacterSize(48);
    _creditButton.buttonText.setFillColor(Color::White);
    _creditButton.buttonText.setOrigin(_creditButton.buttonText.getGlobalBounds().width / 2, _creditButton.buttonText.getGlobalBounds().height / 2);
    _creditButton.buttonText.setPosition(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 2 + _creditButton.buttonSprite.getGlobalBounds().height + 10);

    // load cedits
    _credits.setFont(_data->assets.getFont("game font"));
    _credits.setString("By: Étienne Ménard, Pier-Alexandre Caron, et Camélia Groleau");
    _credits.setCharacterSize(24);
    _credits.setFillColor(Color::White);
    _credits.setOrigin(_credits.getGlobalBounds().width / 2, _credits.getGlobalBounds().height / 2);
    _credits.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);
}

void mainMenuState::handleInput()
{
    Event event;
    while (_data->window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            _data->window.close();
        // click "Credits" button -> toggle credits
        else if (_data->input.isSpriteClicked(_creditButton.buttonSprite, Mouse::Left, _data->window)) {
            _creditsShown = !_creditsShown;
        }
        // click "Play" butoon -> start game
        else if (_data->input.isSpriteClicked(_playButton.buttonSprite, Mouse::Left, _data->window)) {
            _data->machine.addState(stateRef(new gameState(_data)), true);
        }
    }
}

void mainMenuState::update(float dt)
{
    _title->animate(dt);

    if (!_buttonDelay && _clock.getElapsedTime().asSeconds() > TITLE_ANIMATION_DELAY + TITLE_ANIMATION_DURATION + 0.5f)
        _buttonDelay = true;
}

//clear, dessine le background et display la fenêtre. (dt n’est pas utilisé ici)
void mainMenuState::draw(float dt) const
{
    _data->window.clear();

    _data->window.draw(_background);

    _title->draw(); // draw le titre

    if (_buttonDelay) {
        // play button
        _data->window.draw(_playButton.buttonSprite);
        _data->window.draw(_playButton.buttonText);
        // credit button
        _data->window.draw(_creditButton.buttonSprite);
        _data->window.draw(_creditButton.buttonText);
    }

    // draw les credits si ils sont enabled
    if (_creditsShown)
        _data->window.draw(_credits);

    _data->window.display();
}