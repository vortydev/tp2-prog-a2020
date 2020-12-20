/*
 * Author:		Étienne Ménard
 * Date:		13/12/2020
 * File:		entity.h
 * Description:	Template de base des entités (mobs et units) du jeu.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cassert>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "Resources\include\vecteur.hpp"

using namespace sf;
using namespace std;

class entity
{
protected:
    int _id;
    int _type;
    string _name;
    Sprite _sprite;
    string _spriteName;

    // position sur la grid
    int _cellX;
    int _cellY;

    // pour les units (just 0 pour les mobs)
    int _cost;
    bool _new;

    // health
    bool _alive;
    int _maxHP;
    int _curHP;

    // combat
    int _range;
    int _damage;
    int _movement;

    
    Clock _animationClock;
    
    int _animationIterator;

public:
    entity();
    ~entity();

    // ID
    int getID()const;
    void setID(int id);

    // type
    int getType()const;
    void setType(int type);

    // name
    string getName()const;
    void setName(string name);

    // sprite
    Sprite& getSprite();
    void setSprite(gameDataRef data, string sprite, int type, string behavior, string number);
    void setSpriteName(string spriteName);
    string getSpriteName();

    // position on grid
    int getCellX()const;
    int getCellY()const;
    void setCellX(int cellX);
    void setCellY(int cellY);
    void setPosition(int cellX, int cellY);
    bool isOnGrid()const;
    void updatePosition();

    // cost and selling
    int getCost()const;
    void setCost(int cost);
    bool isNew()const;
    void toggleNew();

    // health
    bool isAlive()const;
    void toggleAlive();
    int getMaxHP()const;
    int getCurHP()const;
    void setMaxHP(int hp);
    void setCurHP(int hp);
    void setHP(int hp);
    void healHP();

    // range
    int getRange()const;
    void setRange(int range);

    // damage
    int getDamage()const;
    
    void setDamage(int damage);

    // movement
    int getMovement()const;
    void setMovement(int movement);

    int getSpriteID();
    void setSpriteID(int spriteID);

    
    
};