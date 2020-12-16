/*
 * Author:		�tienne M�nard
 * Date:		15/12/2020
 * File:		behavioredMontser.cpp
 * Description:	D�f�nition des m�thodes de behavioredMontser
 */

#include "behavioredMonster.h"

 // constructeur sans param�tre
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
