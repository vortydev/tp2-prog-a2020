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


characterBehavior behavioredEntity::getBehavior()
{
    return _behavior;
}

void behavioredEntity::setBehavior(characterBehavior behavior)
{
    _behavior = behavior;
}
