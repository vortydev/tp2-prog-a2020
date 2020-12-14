/*
 * Author:		�tienne M�nard
 * Date:		13/12/2020
 * File:		entityManager.cpp
 * Description:	D�f�nitions des m�thodes du entityManager
 */

#include "entityManager.h"

entityManager::entityManager(gameDataRef data) : _data(data)
{
    loadRefEntities();      // initialise le vecteur d'entities de r�f�rence
    loadShopUnits();        // initialise le vecteur de shop units
    //loadBoardEntities();  // initialise la liste de board entities
}

// loads le vecteur de entities de r�f�rences
void entityManager::loadRefEntities()
{
    int id = 0;
    int type, cost, hp, range, damage;
    string name, sprite;

    _entityList.open(ENTITY_LIST_FILEPATH);
    while (!_entityList.eof()) {
        entity tempEntity;

        _entityList >> name >> sprite >> type >> cost >> hp >> range >> damage;
        
        // set les valeurs � l'entity temporaire
        tempEntity.setID(id);
        tempEntity.setType(type);
        tempEntity.setName(name);
        tempEntity.setSprite(_data, sprite, type);
        tempEntity.setHP(hp);
        tempEntity.setRange(range);
        tempEntity.setDamage(damage);
        tempEntity.setCost(cost);

        // push back l'entity temp dans le vecteur de r�f�rences
        _refEntities.push_back(tempEntity);

        id++;
    }
    _entityList.close();
}

// retourne l'entity avec l'id en param�tre
const entity& entityManager::getRefEntity(int id)
{
    assert(id >= 0 && id < _refEntities.size());
    return _refEntities[id];
}

// initialise le vecteur de shop units
void entityManager::loadShopUnits()
{
    for (int i = 0; i < _refEntities.size(); i++) {
        if (_refEntities[i].getType() == 1) {
            _shopUnits.push_back(getRefEntity(i));
        }
    }

    loadShopUnitsCells();
}

void entityManager::loadShopUnitsCells()
{
    for (int i = 0; i < _shopUnits.size(); i++) {
        Sprite tempCell;
        tempCell.setTexture(_data->assets.getTexture("grid cell grey"));
        _shopUnitsCells.push_back(tempCell);
    }
}

void entityManager::drawShopUnits(int currency) const
{
    int slot = 0;
    for (int i = 0; i < _shopUnits.size(); i++) {
        if (_shopUnits[i].getCost() <= currency) {
            Text costText;

            costText.setFont(_data->assets.getFont("game font"));
            costText.setString(to_string(_shopUnits[i].getCost()));
            costText.setCharacterSize(24);
            costText.setFillColor(Color::Black);
            costText.setOrigin(costText.getGlobalBounds().width / 2, costText.getGlobalBounds().height / 2);
            costText.setPosition(85 + slot * 80 + slot * 15 + 40, SCREEN_HEIGHT - 100);

            _shopUnitsCells[i].setPosition(85 + slot * 80 + slot * 15, SCREEN_HEIGHT - 190);
            _shopUnits[i].getSprite().setPosition(85 + 8 + slot * 80 + slot * 15, SCREEN_HEIGHT - 182);

            _data->window.draw(_shopUnitsCells[i]);
            _data->window.draw(_shopUnits[i].getSprite());
            _data->window.draw(costText);

            slot++;
        }
    }
}