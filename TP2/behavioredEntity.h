/*
 * Author:		Étienne Ménard
 * Date:		15/12/2020
 * File:		behavioredEntity.h
 * Description:	Entities sur lesquelles on slap une layer de behavior pour l'animation de leurs sprites et la gestion de combat dans la state wave
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "entity.h"
// #include behavior stuff

class behavioredEntity : public entity{
private:
    
    characterBehavior _behavior;

public:
    behavioredEntity();
    ~behavioredEntity();

    //behavior
    void attackTarget(entity& target);

    void setBehavior(characterBehavior newBehavior);
    characterBehavior getBehavior();
};