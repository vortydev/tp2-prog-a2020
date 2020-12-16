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

entity& behavioredEntity::getEntity()
{
    return _entity;
}

characterBehavior behavioredEntity::getBehavior()
{
    return _behavior;
}

void behavioredEntity::setEntity(const entity& e)
{
    _entity = e;
}

void behavioredEntity::setBehavior(characterBehavior behavior)
{
    _behavior = behavior;
}
