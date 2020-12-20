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

void behavioredEntity::loadAllSprite(gameDataRef data, string sprite)
{
	for (int i = 0; i < 4; i++) {
		string animationName = sprite + "idle000" + to_string(i);
		string path = "Resources/res/entitySprites/unit_" + sprite + "_" + "idle" + "_" + "000" + to_string(i) + ".png";
		data->assets.loadTexture(animationName, path);
		_animationFramesIdle.push_back(data->assets.getTexture(animationName));
	}
	
	for (int i = 0; i < 4; i++) {
		string animationName = sprite + "attack000" + to_string(i);
		string path = "Resources/res/entitySprites/unit_" + sprite + "_" + "attacking" + "_" + "000" + to_string(i) + ".png";
		data->assets.loadTexture(animationName, path);
		_animationFramesIdle.push_back(data->assets.getTexture(animationName));

	}
	
}

void behavioredEntity::animate(gameDataRef data)
{

	if (_animationClock.getElapsedTime().asSeconds() > UNIT_ANIMATION_DURATION / 4)
	{
		if (_animationIterator>=4) {
			_animationIterator = 0;
		}
		switch (_behavior)
		{
		case characterBehavior::idle:
			_sprite.setTexture(_animationFramesIdle.at(_animationIterator));
			_animationIterator++;
			break;
		case characterBehavior::attack:

			break;
		default:
			break;
		}
		_animationClock.restart();
	}
}

