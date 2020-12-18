/*
 * Author:		Étienne Ménard
 * Date:		18/12/2020
 * File:		splashSlime.cpp
 * Description:	Définitions des méthodes du splashSlime.
 */

#include "splashSlime.h"

splashSlime::splashSlime(gameDataRef data) : _data(data)
{
    // load dynamiquement les sprites du slime (smh Cam)
    loadSlimeSprites();

    // set la texture initiale du slime
    _slimeSprite.setTexture(_animationFrames[0]);

    // set l'itérateur de textures au début du vecteur (à 0)
    _animationIterator = 0;

    _slimeSprite.setPosition(_data->window.getSize().x / 2 - _slimeSprite.getGlobalBounds().width / 2, _data->window.getSize().y / 2 - _slimeSprite.getGlobalBounds().height / 2);
}

void splashSlime::draw() const
{
    _data->window.draw(_slimeSprite);
}

void splashSlime::animate(float dt)
{
    //si on veut que l’animation dure .4 seconde et qu’on a 4 images, chaque image
    //durera .1 seconde. D’où la division par la taille du vecteur de frame
    if (_clock.getElapsedTime().asSeconds() > SPLASH_SLIME_ANIMATION_DURATION / _animationFrames.size())
    {
        _animationIterator++;

        // reset l'itérateur au début si on arrivé à la fin du vecteur
        if (_animationIterator >= _animationFrames.size())
            _animationIterator = 0;

        _slimeSprite.setTexture(_animationFrames[_animationIterator]);

        _clock.restart();
    }
}

// push les frames d'animations du slime dans le vecteur
void splashSlime::loadSlimeSprites()
{
    string name, path;
    for (int i = 0; i < 5; i++) {
        name = "slime" + to_string(i);
        path = "Resources/res/entitySprites/mob_slime_sleep_000" + to_string(i) + ".png";

        _data->assets.loadTexture(name, path);
        _animationFrames.push_back(_data->assets.getTexture(name));
    }
}

// retournes le current sprite du slime
const Sprite& splashSlime::getSprite() const {
    return _slimeSprite;
}