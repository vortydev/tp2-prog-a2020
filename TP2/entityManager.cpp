/*
 * Author:		Étienne Ménard
 * Date:		13/12/2020
 * File:		entityManager.cpp
 * Description:	Défénitions des méthodes du entityManager
 */

#include "entityManager.h"

entityManager::entityManager(gameDataRef data) : _data(data)
{
    loadRefEntities();      // initialise le vecteur d'entities de référence
    //loadShopUnits();      // initialise le vecteur de shop units
    //loadBoardEntities();  // initialise la liste de board entities
}

void entityManager::loadRefEntities()
{
    int id = 0;
    int type, hp, range, cost;
    string name, sprite;

    _entityList.open(ENTITY_LIST_FILEPATH);
    while (!_entityList.eof()) {
        entity tempEntity;

        _entityList >> name >> sprite >> type >> hp >> range >> cost;
        
        // set les valeurs à l'entity temporaire
        tempEntity.setID(id);
        tempEntity.setType(type);
        tempEntity.setName(name);
        tempEntity.setSprite(_data, sprite, type);
        tempEntity.setHP(hp);
        tempEntity.setRange(range);
        tempEntity.setCost(cost);

        // push back l'entity temp dans le vecteur de références
        _refEntities.push_back(tempEntity);

        id++;
    }
    _entityList.close();
}