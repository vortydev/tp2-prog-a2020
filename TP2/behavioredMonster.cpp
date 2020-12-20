/*
 * Author:		Étienne Ménard
 * Date:		15/12/2020
 * File:		behavioredMontser.cpp
 * Description:	Défénition des méthodes de behavioredMontser
 */

#include "behavioredMonster.h"

 // constructeur sans paramètre
behavioredMonster::behavioredMonster()
{

}

// destructeur
behavioredMonster::~behavioredMonster()
{

}

void behavioredMonster::attackTarget(entity& target)
{
    target.setHP(target.getCurHP() - getDamage());
}

void behavioredMonster::setBehavior(monsterBehavior newBehavior)
{
    _behavior = newBehavior;
}

monsterBehavior behavioredMonster::getBehavior()
{
    return _behavior;
}