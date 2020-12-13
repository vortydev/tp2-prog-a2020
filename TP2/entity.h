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

using namespace sf;
using namespace std;

class entity
{
private:
    int _id;
    int _type;
    string _name;
    Sprite _sprite;

    int _cellX;
    int _cellY;

    // combat
    bool _alive;
    int _maxHP;
    int _curHP;
    int _range;

    // pour les units (just 0 pour les mobs)
    int _cost;

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
    void setSprite(gameDataRef data, string sprite, int type);

    // position on grid
    int getCellX()const;
    int getCellY()const;
    void setCellX(int cellX);
    void setCellY(int cellY);
    void setPosition(int cellX, int cellY);
    bool isOnGrid()const;
    void updatePosition();

    // alive?
    bool isAlive()const;
    void toggleAlive();

    // health
    int getMaxHP()const;
    int getCurHP()const;
    void setMaxHP(int hp);
    void setCurHP(int hp);
    void setHP(int hp);

    // attack range
    int getRange()const;
    void setRange(int range);

    // cost
    int getCost()const;
    void setCost(int cost);
};