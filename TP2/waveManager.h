/*
 * Author:		Étienne Ménard
 * Date:		15/12/2020
 * File:		waveManager.h
 * Description:	Big boi file qui va s'occuper de la gestion des composants durant le state de wave
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "entityManager.h"

class waveManager
{
private:
    gameDataRef _data;

public:
    waveManager(gameDataRef data);
    ~waveManager();
};