/*
 * Author:		�tienne M�nard
 * Date:		15/12/2020
 * File:		behavioredMonster.h
 * Description:	monstre ou une sprite leur sera assign� ainsi que de nombreuse variables qui lui
 *				seront utile pour affronter les entit�es que le joueurs utilisera
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "entity.h"


class behavioredMonster : public entity{
private:
    
    characterBehavior _behavior;

public:
    behavioredMonster();
    ~behavioredMonster();

    characterBehavior getBehavior();
    
    void setBehavior(characterBehavior behavior);
};