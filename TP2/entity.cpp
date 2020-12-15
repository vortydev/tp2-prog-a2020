/*
 * Author:		�tienne M�nard
 * Date:		13/12/2020
 * File:		entity.cpp
 * Description:	D�f�nition des m�thodes de entity
 */

#include "entity.h"

// constructeur
entity::entity()
{
    // init ints � 0
    _id = _type = _cost = _maxHP = _curHP = _range = _damage = _movement = 0;
    _name = ""; // no name
    // on ne loadera pas de sprites dans la template
    _cellX = _cellY = -1;   // set pos dehors de la grid
    _alive = true;  // sera seulement � false if killed
}

// destructeur
entity::~entity()
{
    _id = _type = _cost = _maxHP = _curHP = _range = _damage = _movement = 0;
    _name = ""; // no name
    _cellX = _cellY = -1;
    _alive = false; // entity is dead
}

entity& entity::getEntity()
{
    return *this;
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
    // change le filepath d�pendant du type d'entity
    switch (type) {
    case 1:
        path = "Resources/res/entitySprites/unit_" + name + "_idle_0000.png";
        break;
    case 2:
        path = "Resources/res/entitySprites/mob_" + name + "_idle_0000.png";
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
    updatePosition();   // mets � jour la position du sprite
}

// set la position y de l'entity sur la grille
void entity::setCellY(int cellY)
{
    _cellY = cellY;     // update la position y
    updatePosition();   // mets � jour la position du sprite
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