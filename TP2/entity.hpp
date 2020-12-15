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

    // position sur la grid
    int _cellX;
    int _cellY;

    // pour les units (just 0 pour les mobs)
    int _cost;

    // health
    bool _alive;
    int _maxHP;
    int _curHP;

    // combat
    int _range;
    int _damage;
    int _movement;

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

    // cost
    int getCost()const;
    void setCost(int cost);

    // health
    bool isAlive()const;
    void toggleAlive();
    int getMaxHP()const;
    int getCurHP()const;
    void setMaxHP(int hp);
    void setCurHP(int hp);
    void setHP(int hp);

    // range
    int getRange()const;
    void setRange(int range);

    // damage
    int getDamage()const;
    void setDamage(int damage);

    // movement
    int getMovement()const;
    void setMovement(int movement);
};

// constructeur
entity::entity()
{
    // init ints à 0
    _id = _type = _cost = _maxHP = _curHP = _range = _damage = _movement = 0;
    _name = ""; // no name
    // on ne loadera pas de sprites dans la template
    _cellX = _cellY = -1;   // set pos dehors de la grid
    _alive = true;  // sera seulement à false if killed
}

// destructeur
entity::~entity()
{
    _id = _type = _cost = _maxHP = _curHP = _range = _damage = _movement = 0;
    _name = ""; // no name
    _cellX = _cellY = -1;
    _alive = false; // entity is dead
}

// retournes l'id de l'entity
int entity::getID() const
{
    return _id;
}

// set l'id de l'entity
void entity::setID(int id)
{
    assert(id >= 0);
    _id = id;
}

// retournes le type de l'entity
int entity::getType() const
{
    return _type;
}

// set le type de l'entity
void entity::setType(int type)
{
    assert(type >= 0 && type < 3);  // on veut un type de 0, 1 ou 2 seulement
    _type = type;
}

// retournes le nom de l'entity
string entity::getName() const
{
    return _name;
}

// set le nom de l'entity
void entity::setName(string name)
{
    assert(name != "");
    _name = name;
}

// retournes le sprite de l'entity
Sprite& entity::getSprite()
{
    return _sprite;
}

// set le sprite de l'entity en utilisant le asset manager
void entity::setSprite(gameDataRef data, string name, int type)
{
    string path;
    // change le filepath dépendant du type d'entity
    switch (type) {
    case 1:
        path = "Resources/res/unit_" + name + ".png";
        break;
    case 2:
        path = "Resources/res/mob_" + name + ".png";
        break;
    }

    data->assets.loadTexture(name, path);
    _sprite.setTexture(data->assets.getTexture(name));
}

// retournes la position x de l'entity sur la grille
int entity::getCellX() const
{
    return _cellX;
}

// retournes la position y de l'entity sur la grille
int entity::getCellY() const
{
    return _cellY;
}

// set la position x de l'entity sur la grille
void entity::setCellX(int cellX)
{
    _cellX = cellX;     // update la position x
    updatePosition();   // mets à jour la position du sprite
}

// set la position y de l'entity sur la grille
void entity::setCellY(int cellY)
{
    _cellY = cellY;     // update la position y
    updatePosition();   // mets à jour la position du sprite
}

// set la position de l'entity sur la grille
void entity::setPosition(int cellX, int cellY)
{
    setCellX(cellX);    // update la position x
    setCellY(cellY);    // update la position y
}

// check si l'entity est sur la grid
bool entity::isOnGrid() const
{
    return (_cellX >= 0 && _cellX < 10) && (_cellY >= 0 && _cellY < 5);
}

// set la position du sprite sur la grille
void entity::updatePosition()
{
    if (isOnGrid())
        _sprite.setPosition(80 * _cellX + 240 + 8, 80 * _cellY + 50 + 8); // needs tweaking
}

// retournes le cost de l'entity
int entity::getCost() const
{
    return _cost;
}

// set le cost de l'entity
void entity::setCost(int cost)
{
    assert(cost >= 0);
    _cost = cost;
}

// retournes si l'entity est en vie
bool entity::isAlive() const
{
    return _alive;
}

// toggle le bool _alive de l'entity
void entity::toggleAlive()
{
    _alive = !_alive;
}

// retournes le max health de l'entity
int entity::getMaxHP() const
{
    return _maxHP;
}

// retournes le current health de l'entity
int entity::getCurHP() const
{
    return _curHP;
}

// set le max health de l'entity
void entity::setMaxHP(int hp)
{
    assert(hp >= 0);
    _maxHP = hp;
}

// set le current health de l'entity
void entity::setCurHP(int hp)
{
    assert(hp >= 0);
    _curHP = hp;
}

// set le max et current health
void entity::setHP(int hp)
{
    setMaxHP(hp);
    setCurHP(hp);
}

// retournes le attack range de l'entity
int entity::getRange() const
{
    return _range;
}

// set l'attack range de l'entity
void entity::setRange(int range)
{
    assert(range > 0);
    _range = range;
}

// retournes le dommage de l'entity
int entity::getDamage() const
{
    return _damage;
}

// set le dommage de l'entity
void entity::setDamage(int damage)
{
    assert(damage > 0);
    _damage = damage;
}

// retournes le nb de cells que l'entity peut parcourir d'une shot
int entity::getMovement() const
{
    return _movement;
}

// set le movement de l'entity
void entity::setMovement(int movement)
{
    assert(movement > 0);
    _movement = movement;
}