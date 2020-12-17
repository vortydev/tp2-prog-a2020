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


characterBehavior behavioredEntity::getBehavior()
{
    return _behavior;
}

void behavioredEntity::setBehavior(characterBehavior behavior)
{
    _behavior = behavior;
}
