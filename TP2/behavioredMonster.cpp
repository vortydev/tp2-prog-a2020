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

entity& behavioredMonster::getEntity()
{
    return _entity;
}

characterBehavior behavioredMonster::getBehavior()
{
    return _behavior;
}

void behavioredMonster::setEntity(const entity& e)
{
    _entity = e;
}

void behavioredMonster::setBehavior(characterBehavior behavior)
{
    _behavior = behavior;
}
