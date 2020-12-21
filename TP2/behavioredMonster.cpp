/*
 * Author:		Pier-Alexandre Caron
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

void behavioredMonster::loadAllSprite(gameDataRef data, string sprite)
{
	for (int i = 0; i < 4; i++) {
		string animationName = sprite + "moving000" + to_string(i);
		string path = "Resources/res/entitySprites/mob_" + sprite + "_" + "moving" + "_" + "000" + to_string(i) + ".png";
		data->assets.loadTexture(animationName, path);
		_animationFramesMoving.push_back(data->assets.getTexture(animationName));
	}

	for (int i = 0; i < 4; i++) {
		string animationName = sprite + "attack000" + to_string(i);
		string path = "Resources/res/entitySprites/mob_" + sprite + "_" + "attacking" + "_" + "000" + to_string(i) + ".png";
		data->assets.loadTexture(animationName, path);
		_animationFramesAttack.push_back(data->assets.getTexture(animationName));
		
	}
}

void behavioredMonster::animate(gameDataRef data)
{
	if (_animationClock.getElapsedTime().asSeconds() > UNIT_ANIMATION_DURATION / 4)
	{
		if (_animationIterator >= 4) {
			_animationIterator = 0;
		}
		switch (_behavior)
		{
		case monsterBehavior::moving:
			_sprite.setTexture(_animationFramesMoving.at(_animationIterator));
			_animationIterator++;
			break;
		case monsterBehavior::attackM:
			_sprite.setTexture(_animationFramesAttack.at(_animationIterator));
			_animationIterator++;
			break;
		default:
			break;
		}
		_animationClock.restart();
	}
}

void behavioredMonster::move()
{
	if (_moveClock.getElapsedTime().asSeconds() > UNIT_ANIMATION_DURATION )
	{
		setCellX(getCellX() - 1);
		_moveClock.restart();
	}
}

void behavioredMonster::leaked()
{
	receiveDamage(getCurHP());
}
