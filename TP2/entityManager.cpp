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
	loadShopUnitsCells();   // initialise le vecteur de cells pour les shop units
}

// loads le vecteur de entities de r�f�rences
void entityManager::loadRefEntities()
{
	int id = 0;
	int type, cost, hp, range, damage, movement;
	string name, sprite;

	_entityList.open(ENTITY_LIST_FILEPATH);
	while (!_entityList.eof()) {
		behavioredEntity tempEntity;

		_entityList >> name >> sprite >> type >> cost >> hp >> range >> damage >> movement;
		tempEntity.setBehavior(characterBehavior::idle);
		tempEntity.setSpriteID(0);
		tempEntity.loadAllSprite(_data,sprite);

		// set les valeurs � l'entity temporaire
		tempEntity.setID(id);
		tempEntity.setType(type);
		tempEntity.setName(name);
		tempEntity.setSprite(_data, sprite, type,"idle","0000");
		tempEntity.setSpriteName(sprite);
		tempEntity.setCost(cost);
		tempEntity.setHP(hp);
		tempEntity.setRange(range);
		tempEntity.setDamage(damage);
		tempEntity.setMovement(movement);

		// push back l'entity temp dans le vecteur de r�f�rences
		_refEntities.push_back(tempEntity);

		id++;
	}
	_entityList.close();
}

void entityManager::loadRefMonster()
{
	int id = 0;
	int type, cost, hp, range, damage, movement;
	string name, sprite;

	_entityList.open(MONTSER_LIST_FILEPATH);
	while (!_entityList.eof()) {
		behavioredMonster tempMonster;

		_entityList >> name >> sprite >> type >> cost >> hp >> range >> damage >> movement;

		// set les valeurs � l'entity temporaire
		tempMonster.setID(id);
		tempMonster.setType(type);
		tempMonster.setName(name);
		tempMonster.setSprite(_data, sprite, type,"moving","0000");
		tempMonster.setCost(cost);
		tempMonster.setHP(hp);
		tempMonster.setRange(range);
		tempMonster.setDamage(damage);
		tempMonster.setMovement(movement);

		// push back l'entity temp dans le vecteur de r�f�rences
		_refMonster.push_back(tempMonster);

		id++;
	}
	_entityList.close();
}

// retourne l'entity avec l'id en param�tre
const behavioredEntity& entityManager::getRefEntity(int id)
{
	assert(id >= 0 && id < _refEntities.size());
	return _refEntities[id];
}

const behavioredMonster& entityManager::getRefMonster(int id)
{
	assert(id >= 0 && id < _refMonster.size());
	return _refMonster[id];
}

// initialise le vecteur de shop units
void entityManager::loadShopUnits()
{
	for (int i = 0; i < _refEntities.size(); i++) {
		//if (_refEntities[i].getType() == 1) {
			_shopUnits.push_back(getRefEntity(i));
		//}
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

// retournes la cellule cliqu�e
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

// toggles si la cell est selectionn�e
void entityManager::setSelected(int cellX, cell& c)
{
	// if no cell has been selected yet
	if (c.cellX == -1) {
		c.cellX = cellX;
		setSelected(_shopUnitsCells[cellX]);
	}
	// if la cell est diff�rente de celle d�j� selectionn�e
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

// retournes le nombre d'entit�s dans la liste
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

// retourne l'entity sur le board � l'emplacement de la cell en param�tre
const behavioredEntity& entityManager::getBoardEntity(cell c)
{
	list<behavioredEntity>::iterator it = _boardEntities.begin();
	while (it != _boardEntities.end()) {
		if (_boardEntities[it].getCellX() == c.cellX && _boardEntities[it].getCellY() == c.cellY)
			return _boardEntities[it];
		else
			it++;
	}
}

// retourne si il y a une unit sur la cell en param�tre
const bool entityManager::isBoardUnitOnCell(cell c)
{
	list<behavioredEntity>::iterator it = _boardEntities.begin();
	while (it != _boardEntities.end()) {
		if (_boardEntities[it].getCellX() == c.cellX && _boardEntities[it].getCellY() == c.cellY)
			return true;
		else
			it++;
	}

	return false;
}

// retourne si il y a un mob sur la cell en param�tre
const bool entityManager::isBoardMobOnCell(cell c)
{
	list<behavioredMonster>::iterator it = _boardMonster.begin();
	while (it != _boardMonster.end()) {
		if (_boardMonster[it].getCellX() == c.cellX && _boardMonster[it].getCellY() == c.cellY)
			return true;
		else
			it++;
	}

	return false;
}

// ajoutes l'unit� dans la liste d'entit�s sur le board
void entityManager::addUnitToBoard(const cell& cU, const cell& cP)
{
	behavioredEntity temp;
	temp = getRefEntity(_shopUnits[cU.cellX].getID());
	temp.setPosition(cP.cellX, cP.cellY);

	list<behavioredEntity>::iterator it = _boardEntities.begin();
	it = _boardEntities.insert(it, temp);
}

// draw les entit�s dans la board list
void entityManager::drawBoardEntities()
{
	list<behavioredEntity>::iterator it = _boardEntities.begin();
	while (it != _boardEntities.end()) {
		if (_boardEntities[it].isAlive())
			_data->window.draw(_boardEntities[it].getSprite());

		it++;
	}
}

// supprime de la liste les entit�s mortes
void entityManager::cleanBoard()
{
	list<behavioredEntity>::iterator it = _boardEntities.begin();
	while (it != _boardEntities.end()) {
		if (!_boardEntities[it].isAlive())
			it = _boardEntities.erase(it);
		else {
			_boardEntities[it].toggleNew();
			it++;
		}
	}
}

// remet � full HP les entities sur le board
void entityManager::revitalizeEntities()
{
	list<behavioredEntity>::iterator it = _boardEntities.begin();
	while (it != _boardEntities.end()) {
		_boardEntities[it].healHP();
		it++;
	}
}

// ach�te l'unit�
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
		if (_boardEntities[it].getCellX() == c.cellX && _boardEntities[it].getCellY() == c.cellY) {
			if (_boardEntities[it].isNew())
				currency += _boardEntities[it].getCost();
			else
				currency += _boardEntities[it].getCost() / 2;

			it = _boardEntities.erase(it);
		}
		else
			it++;
	}
}



void entityManager::update(float dt)
{
	

	for (list<behavioredEntity>::iterator it = _boardEntities.begin(); it != _boardEntities.end(); it++) {
		_boardEntities[it].animate(_data);
	}
}



