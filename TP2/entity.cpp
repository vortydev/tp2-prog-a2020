/*
 * Author:		Étienne Ménard
 * Date:		13/12/2020
 * File:		entity.cpp
 * Description:	Défénitions des méthodes de entity
 */

#include "entity.h"

entity::entity(gameDataRef data) : _data(data)
{
    _id = 0;
    _name = "";
    // on ne loadera pas de sprites dans la template

    // on mets la position de base hors de la grid
    _cellX = -1;
    _cellY = -1;

    _alive = false;
    _maxHealth = _curHealth = 0;
    _attackRange = 0;
    _cost = 0;
}

// destructeur
entity::~entity()
{
    _id = 0;
    _name = "";
    _cellX = -1;
    _cellY = -1;
    _alive = false;
    _maxHealth = _curHealth = 0;
    _attackRange = 0;
    _cost = 0;
}

// draw l'entity
void entity::drawEntity() const
{
    _data->window.draw(_sprite);
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
void entity::setSprite(string name)
{
    _sprite.setTexture(_data->assets.getTexture(name));
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
    updatePosition();   // mets à jour la position du sprite
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
        _sprite.setPosition(80 * _cellX + 240 + 14, 80 * _cellY + 50 + 14); // needs tweaking
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
int entity::getMaxHealth() const
{
    return _maxHealth;
}

// retournes le current health de l'entity
int entity::getCurHealth() const
{
    return _curHealth;
}

// set le max health de l'entity
void entity::setMaxHealth(int health)
{
    assert(health >= 0);
    _maxHealth = health;
}

// set le current health de l'entity
void entity::setCurHealth(int health)
{
    assert(health >= 0);
    _curHealth = health;
}

// set le max et current health
void entity::setHealth(int health)
{
    setMaxHealth(health);
    setCurHealth(health);
}

// retournes le attack range de l'entity
int entity::getAttackRange() const
{
    return _attackRange;
}

// set l'attack range de l'entity
void entity::setAttackRange(int range)
{
    assert(range >= 0);
    _attackRange = range;
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