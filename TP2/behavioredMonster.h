/*
 * Author:		Pier-Alexandre Caron
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
    
    monsterBehavior _behavior;

    vecteur<Texture> _animationFramesMoving;
    vecteur<Texture> _animationFramesAttack;

    Clock _moveClock;

public:
    behavioredMonster();
    ~behavioredMonster();

    //behavior
    void attackTarget(entity& target);

    void setBehavior(monsterBehavior newBehavior);
    monsterBehavior getBehavior();

    void loadAllSprite(gameDataRef data, string sprite);
    void animate(gameDataRef data);
    
    void move();
    void leaked();
};