/*
 * Author:		Étienne Ménard
 * Date:		18/12/2020
 * File:		splashSlime.h
 * Description:	Petit objet pour la gestion du sprite du slime sur le splash screen.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "DEFINITIONS.hpp"
#include "game.h"

#include "Resources/include/vecteur.hpp"

using namespace sf;

// ma référence: https://github.com/vortydev/sfml-flappybird/blob/master/Lab8_FlappyBird/bird.h
class splashSlime
{
private:
    gameDataRef _data;
    Sprite _slimeSprite;

    Clock _clock;
    vecteur<Texture> _animationFrames;
    int _animationIterator;

public:
    splashSlime(gameDataRef data);

    void draw()const;
    void animate(float dt);

    // push les frames d'animations du slime dans le vecteur
    void loadSlimeSprites();

    const Sprite& getSprite()const;
};