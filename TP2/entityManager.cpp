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
        it++;
    }

    return size;
}

// retourne l'entity sur le board à l'emplacement de la cell en paramètre
const entity& entityManager::getBoardEntity(cell c)
{
    list<behavioredEntity>::iterator it = _boardEntities.begin();
    while (it != _boardEntities.end()) {
        if (_boardEntities[it].getEntity().getCellX() == c.cellX && _boardEntities[it].getEntity().getCellY() == c.cellY)
            return _boardEntities[it].getEntity();
        else
            it++;
    }
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

// draw les entités dans la board list
void entityManager::drawBoardEntities()
{
    list<behavioredEntity>::iterator it = _boardEntities.begin();
    while (it != _boardEntities.end()) {
        if (_boardEntities[it].getEntity().isAlive())
            _data->window.draw(_boardEntities[it].getEntity().getSprite());

        it++;
    }
}

// supprime de la liste les entités mortes
void entityManager::cleanBoard()
{
    list<behavioredEntity>::iterator it = _boardEntities.begin();
    while (it != _boardEntities.end()) {
        if (!_boardEntities[it].getEntity().isAlive())
            it = _boardEntities.erase(it);
        else {
            _boardEntities[it].getEntity().toggleNew();
            it++;
        }
    }
}

// remet à full HP les entities sur le board
void entityManager::revitalizeEntities()
{
    list<behavioredEntity>::iterator it = _boardEntities.begin();
    while (it != _boardEntities.end()) {
        _boardEntities[it].getEntity().healHP();
        it++;
    }
}

// achète l'unité
void entityManager::buyUnit(const cell& c, int& currency)
{
    currency -= _shopUnits[c.cellX].getCost();

    if (currency < 0)
        currency = 0;
}

void entityManager::sellUnit(const cell& c, int& currency)
{
    list<behavioredEntity>::iterator it = _boardEntities.begin();
    while (it != _boardEntities.end()) {
        if (_boardEntities[it].getEntity().getCellX() == c.cellX && _boardEntities[it].getEntity().getCellY() == c.cellY) {
            if (_boardEntities[it].getEntity().isNew())
                currency += _boardEntities[it].getEntity().getCost();
            else
                currency += _boardEntities[it].getEntity().getCost() / 2;

            it = _boardEntities.erase(it);
        }
        else
            it++;
    }
}

void entityManager::processEntityBehavior(void)
{
    //entity behavior
    for (list<behavioredEntity>::iterator it = _boardEntities.begin(); it != _boardEntities.end(); it++) {

        if (_boardEntities[it].getBehavior() == characterBehavior::idle) {

            //check si dans un certain range 2 case devant 1 diagonale + coté
            for (list<behavioredMonster>::iterator itM = _boardMonster.begin(); itM != _boardMonster.end(); itM++) {

                /*va devenir it.isInRange(itM) dans le if*/
                if (_boardEntities[it].getEntity().getCellY() - _boardMonster[itM].getEntity().getCellY()/* <= something */) {
                    /* méthode it.chasing(itm) retient le target + change le behavior*/
                    _boardEntities[it].setBehavior(characterBehavior::chasing);
                }
            }
        }

        if (_boardEntities[it].getBehavior() == characterBehavior::chasing) {
            //se deplace vers son target trouver dans idle moveTowardTarget()

            //check si path bloqué utilise path alternatif
        }

        if (_boardEntities[it].getBehavior() == characterBehavior::attack) {
            //attack le target lorsque in range     attackTarget()
            //retourne un bool pour effacer le target et changer la behavior
        }
    }

    //monster behavior va etre refait
    for (list<behavioredMonster>::iterator itM = _boardMonster.begin(); itM != _boardMonster.end(); itM++) {

        if (_boardMonster[itM].getBehavior() == monsterBehavior::moving) {
            //va vers la gauche si un target est trouvé il va vers le target
            if (/*An enemy is in range*/false) {

            }
            else {
                /*move right*/
            }
        }

        else if (_boardMonster[itM].getBehavior() == monsterBehavior::engage) {
            //se deplace vers son target trouver dans moving

            //check si path bloqué utilise path alternatif
        }

        else if (_boardMonster[itM].getBehavior() == monsterBehavior::attacking) {
            //attack le target lorsque in range
        }
    }
}


