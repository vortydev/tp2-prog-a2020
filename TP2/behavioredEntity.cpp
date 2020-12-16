/*
 * Author:		Étienne Ménard
 * Date:		15/12/2020
 * File:		behavioredEntity.cpp
 * Description:	Défénition des méthodes de behavioredEntity
 */

#include "behavioredEntity.h"

 // constructeur sans paramètre
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
