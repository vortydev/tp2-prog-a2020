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
    gameDataRef _data;

    int _id;
    string _name;
    Sprite _sprite;

    int _cellX;
    int _cellY;

    // combat
    bool _alive;
    int _maxHealth;
    int _curHealth;
    int _attackRange;

    // pour les units (just 0 pour les mobs)
    int _cost;

public:
    entity(gameDataRef data);
    ~entity();

    void drawEntity()const;

    // ID
    int getID()const;
    void setID(int id);

    // name
    string getName()const;
    void setName(string name);

    // sprite
    Sprite& getSprite();
    void setSprite(string sprite);

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
    int getMaxHealth()const;
    int getCurHealth()const;
    void setMaxHealth(int health);
    void setCurHealth(int health);
    void setHealth(int health);

    // attack range
    int getAttackRange()const;
    void setAttackRange(int range);

    // cost
    int getCost()const;
    void setCost(int cost);
};