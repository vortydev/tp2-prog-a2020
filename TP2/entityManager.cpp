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

    loadShopUnits();        // initialise le vecteur de shop units
    loadShopUnitsCells();   // initialise le vecteur de cells pour les shop units
}

// loads le vecteur de entities de références
void entityManager::loadRefEntities()
{
    int id = 0;
    int type, cost, hp, range, damage, movement;
    string name, sprite;

    _entityList.open(ENTITY_LIST_FILEPATH);
    while (!_entityList.eof()) {
        entity tempEntity;

        _entityList >> name >> sprite >> type >> cost >> hp >> range >> damage >> movement;
        
        // set les valeurs à l'entity temporaire
        tempEntity.setID(id);
        tempEntity.setType(type);
        tempEntity.setName(name);
        tempEntity.setSprite(_data, sprite, type);
        tempEntity.setCost(cost);
        tempEntity.setHP(hp);
        tempEntity.setRange(range);
        tempEntity.setDamage(damage);
        tempEntity.setMovement(movement);

        // push back l'entity temp dans le vecteur de références
        _refEntities.push_back(tempEntity);

        id++;
    }
    _entityList.close();
}

// retourne l'entity avec l'id en paramètre
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
}

// load le vecteur de cellules pour les shop units
void entityManager::loadShopUnitsCells()
{
    for (int i = 0; i < _shopUnits.size(); i++) {
        cell tempCell;

        tempCell.sprite.setTexture(_data->assets.getTexture("grid cell grey"));
        tempCell.cellX = i;
        tempCell.selected = false;

        _shopUnitsCells.push_back(tempCell);
    }
}

// draw les units qui sont affordables
void entityManager::drawShopUnits(const int currency) const
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

            _shopUnitsCells[i].sprite.setPosition(85 + slot * 80 + slot * 15, SCREEN_HEIGHT - 190);
            _shopUnits[i].getSprite().setPosition(85 + 8 + slot * 80 + slot * 15, SCREEN_HEIGHT - 182);

            if (_shopUnitsCells[i].selected)
                _shopUnitsCells[i].sprite.setTexture(_data->assets.getTexture("grid cell green"));
            else 
                _shopUnitsCells[i].sprite.setTexture(_data->assets.getTexture("grid cell grey"));

            _data->window.draw(_shopUnitsCells[i].sprite);
            _data->window.draw(_shopUnits[i].getSprite());
            _data->window.draw(costText);

            slot++;
        }
    }
}

// retournes la cellule cliquée
cell& entityManager::getShopUnitCell(gameDataRef data) const
{
    for (int i = 0; i < _shopUnitsCells.size(); i++) {
        if (data->input.isSpriteClicked(_shopUnitsCells[i].sprite, Mouse::Left, data->window))
            return _shopUnitsCells[i];
    }
}

// toggles the cell as selected or not
void entityManager::setSelected(cell& c)
{
    c.selected = !c.selected;
}

// toggles si la cell est selectionnée
void entityManager::setSelected(int cellX, cell& c)
{
    // if no cell has been selected yet
    if (c.cellX == -1) {
        c.cellX = cellX;
        setSelected(_shopUnitsCells[cellX]);
    }
    // if la cell est différente de celle déjà selectionnée
    else if (c.cellX != cellX) {
        // deselects the previous cell
        setSelected(_shopUnitsCells[c.cellX]);

        // set the new cell's position
        c.cellX = cellX;

        // selects the new cell
        setSelected(_shopUnitsCells[cellX]);
    }
}

// unselects the selected cell
void entityManager::unSelectCell(cell& c)
{
    setSelected(_shopUnitsCells[c.cellX]);
    c.cellX = -1;
}

// retournes le nombre d'entités dans la liste
const int entityManager::boardEntitiesSize()
{
    int size = 0;
    list<behavioredEntity>::iterator it = _boardEntities.begin();
    while (it != _boardEntities.end()) {
        size++;
    }

    return size;
}

// ajoutes l'unité dans la liste d'entités sur le board
void entityManager::addUnitToBoard(const cell& cU, const cell& cP)
{
    behavioredEntity temp;
    temp.setEntity(getRefEntity(_shopUnits[cU.cellX].getID()));
    temp.getEntity().setPosition(cP.cellX, cP.cellY);

    list<behavioredEntity>::iterator it = _boardEntities.begin();
    it = _boardEntities.insert(it, temp);
}

// effectues la transaction monétaire
void entityManager::unitTransaction(const cell& c, int& currency)
{
    currency -= _shopUnits[c.cellX].getCost();

    if (currency < 0)
        currency = 0;
}

// draw les entités dans la board list
void entityManager::drawBoardEntities()
{
    list<behavioredEntity>::iterator it = _boardEntities.begin();
    while (it != _boardEntities.end()) {
        _data->window.draw(_boardEntities[it].getEntity().getSprite());
        it++;
    }
}