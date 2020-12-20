/*
 * Author:		�tienne M�nard
 * Date:		15/12/2020
 * File:		behavioredEntity.cpp
 * Description:	D�f�nition des m�thodes de behavioredEntity
 */

#include "behavioredEntity.h"

 // constructeur sans param�tre
behavioredEntity::behavioredEntity()
{

}

// destructeur
behavioredEntity::~behavioredEntity()
{

}

void behavioredEntity::attackTarget(entity& target)
{
    target.setHP(target.getCurHP() - getDamage());
}

void behavioredEntity::setBehavior(characterBehavior newBehavior)
{
    _behavior = newBehavior;
}

characterBehavior behavioredEntity::getBehavior()
{
    return _behavior;
}