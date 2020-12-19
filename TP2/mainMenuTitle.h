/*
 * Author:		Étienne Ménard
 * Date:		18/12/2020
 * File:		mainMenuTitle.h
 * Description:	Objet pour gérer le titre du main menu
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "DEFINITIONS.hpp"
#include "game.h"

using namespace sf;

class mainMenuTitle
{
private:
    gameDataRef _data;
    Clock _clock;

    Text _title;
    Text _titleShadow;

    bool _titleDelay;

public:
    mainMenuTitle(gameDataRef data);

    void draw()const;
    void animate(float dt);
};