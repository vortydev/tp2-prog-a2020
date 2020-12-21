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
	loadRefMonster();

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
		behavioredEntity tempEntity;

		_entityList >> name >> sprite >> type >> cost >> hp >> range >> damage >> movement;
		tempEntity.setBehavior(characterBehavior::idle);
		tempEntity.setSpriteID(0);
		tempEntity.loadAllSprite(_data, sprite);

		// set les valeurs à l'entity temporaire
		tempEntity.setID(id);
		tempEntity.setType(type);
		tempEntity.setName(name);
		tempEntity.setSprite(_data, sprite, type, "idle", "0000");
		tempEntity.setSpriteName(sprite);
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

void entityManager::loadRefMonster()
{
	int id = 0;
	int type, cost, hp, range, damage, movement;
	string name, sprite;

	_entityList.open(MONTSER_LIST_FILEPATH);
	while (!_entityList.eof()) {
		behavioredMonster tempMonster;

		_entityList >> name >> sprite >> type >> cost >> hp >> range >> damage >> movement;
		tempMonster.setBehavior(monsterBehavior::moving);
		tempMonster.setSpriteID(0);
		tempMonster.loadAllSprite(_data, sprite);

		// set les valeurs à l'entity temporaire
		tempMonster.setID(id);
		tempMonster.setType(type);
		tempMonster.setName(name);
		tempMonster.setSprite(_data, sprite, type, "moving", "0000");
		tempMonster.setCost(cost);
		tempMonster.setHP(hp);
		tempMonster.setRange(range);
		tempMonster.setDamage(damage);
		tempMonster.setMovement(movement);

		// push back l'entity temp dans le vecteur de références
		_refMonster.push_back(tempMonster);

		id++;
	}
	_entityList.close();
}

// retourne l'entity avec l'id en paramètre
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

// retourne si il y a une unit sur la cell en paramètre
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

// retourne si il y a un mob sur la cell en paramètre
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

// ajoutes l'unité dans la liste d'entités sur le board
void entityManager::addUnitToBoard(const cell& cU, const cell& cP)
{
	behavioredEntity temp;
	temp = getRefEntity(_shopUnits[cU.cellX].getID());
	temp.setPosition(cP.cellX, cP.cellY);

	list<behavioredEntity>::iterator it = _boardEntities.begin();
	it = _boardEntities.insert(it, temp);
}

// draw les entités dans la board list
void entityManager::drawBoardEntities()
{
	list<behavioredEntity>::iterator it = _boardEntities.begin();
	while (it != _boardEntities.end()) {
		if (_boardEntities[it].isAlive())
			_data->window.draw(_boardEntities[it].getSprite());

		it++;
	}
	list<behavioredMonster>::iterator itm = _boardMonster.begin();
	while (itm != _boardMonster.end()) {
		if (_boardMonster[itm].isAlive())
			_data->window.draw(_boardMonster[itm].getSprite());

		itm++;
	}
}

// supprime de la liste les entités mortes
int entityManager::cleanBoard(grid* g)
{
	int deadMobLoot = 0;

	list<behavioredEntity>::iterator it = _boardEntities.begin();
	while (it != _boardEntities.end()) {
		if (!_boardEntities[it].isAlive()) {
			g->setOccupied(_boardEntities[it].getCellX(), _boardEntities[it].getCellY());
			it = _boardEntities.erase(it);
		}
		else {
			_boardEntities[it].toggleNew();
			it++;
		}
	}
	list<behavioredMonster>::iterator itm = _boardMonster.begin();
	while (itm != _boardMonster.end()) {
		if (!_boardMonster[itm].isAlive()) {
			deadMobLoot += (_boardMonster[itm].getID() + 1) * 3;
			itm = _boardMonster.erase(itm);
		}
		else {
			_boardMonster[itm].toggleNew();
			itm++;
		}
	}
	return deadMobLoot;
}

void entityManager::cleanLeakers()
{
	list<behavioredMonster>::iterator itm = _boardMonster.begin();
	while (itm != _boardMonster.end()) {
		if (!_boardMonster[itm].isAlive()) {
			itm = _boardMonster.erase(itm);
		}
		else {
			_boardMonster[itm].toggleNew();
			itm++;
		}
	}
}

// remet à full HP les entities sur le board
void entityManager::revitalizeEntities()
{
	list<behavioredEntity>::iterator it = _boardEntities.begin();
	while (it != _boardEntities.end()) {
		_boardEntities[it].setSprite(_data, _boardEntities[it].getSpriteName(), 1, "idle", "0000");
		_boardEntities[it].healHP();
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

	//pour chaque unit
	for (list<behavioredEntity>::iterator it = _boardEntities.begin(); it != _boardEntities.end(); it++) {
		_boardEntities[it].animate(_data);
	}

	//pour chaque monstres
	for (list<behavioredMonster>::iterator itm = _boardMonster.begin(); itm != _boardMonster.end(); itm++) {
		_boardMonster[itm].animate(_data);

	}
	checkMonsterInRange();
	checkEntityInRange();


}

void entityManager::loadWave(int wave)
{
	list<behavioredMonster>::iterator itm = _boardMonster.begin();

	int idL1 = 0 + (wave / 3);
	if (idL1 >= 4) idL1 = 3;

	int idL2 = 0 + (wave / 4);
	if (idL2 >= 4) idL2 = 3;

	int idL3 = 0 + (wave / 6);
	if (idL3 >= 4) idL3 = 3;

	int idL4 = 0 + (wave / 8);
	if (idL4 >= 4) idL4 = 3;


	for (int i = 0; i < 5; i++) {
		behavioredMonster temp = getRefMonster(idL1);
		temp.setPosition(9, i);

		itm = _boardMonster.insert(itm, temp);
	}
	if (wave > 4) {
		for (int i = 0; i < 5; i++) {
			behavioredMonster temp = getRefMonster(idL2);
			temp.setPosition(10, i);

			itm = _boardMonster.insert(itm, temp);
		}
	}
	if (wave > 6) {
		for (int i = 0; i < 5; i++) {
			behavioredMonster temp = getRefMonster(idL3);
			temp.setPosition(11, i);

			itm = _boardMonster.insert(itm, temp);
		}
	}
	if (wave > 8) {
		for (int i = 0; i < 5; i++) {
			behavioredMonster temp = getRefMonster(idL4);
			temp.setPosition(12, i);

			itm = _boardMonster.insert(itm, temp);
		}
	}

}

void entityManager::checkMonsterInRange()
{
	//pour chaque Entité
	for (list<behavioredEntity>::iterator it = _boardEntities.begin(); it != _boardEntities.end(); it++) {

		//pour chaque monstre
		for (list<behavioredMonster>::iterator itm = _boardMonster.begin(); itm != _boardMonster.end(); itm++) {
			if (_boardEntities[it].getCellY() == _boardMonster[itm].getCellY() &&
				_boardEntities[it].getCellX() == _boardMonster[itm].getCellX() - 1)
			{
				_boardEntities[it].setBehavior(characterBehavior::attack);
				break;
			}
			else {
				_boardEntities[it].setBehavior(characterBehavior::idle);
			}
		}

		if (_boardEntities[it].getBehavior() == characterBehavior::attack) {

			//cherche le entity qui est devant moi
			for (list<behavioredMonster>::iterator itm = _boardMonster.begin(); itm != _boardMonster.end(); itm++) {
				if (_boardEntities[it].getCellY() == _boardMonster[itm].getCellY() &&
					_boardEntities[it].getCellX() == _boardMonster[itm].getCellX() - 1)
				{

					_boardEntities[it].attack(_boardMonster[itm]);

				}
			}
		}
	}
}

void entityManager::checkEntityInRange()
{
	//pour tout les monstres
	for (list<behavioredMonster>::iterator itm = _boardMonster.begin(); itm != _boardMonster.end(); itm++) {

		//si un entité enemmi est devant nou
		for (list<behavioredEntity>::iterator it = _boardEntities.begin(); it != _boardEntities.end(); it++) {

			if (_boardEntities[it].getCellY() == _boardMonster[itm].getCellY() &&
				_boardEntities[it].getCellX() == _boardMonster[itm].getCellX() - 1)
			{
				_boardMonster[itm].setBehavior(monsterBehavior::attackM);
				break;
			}
			else {
				_boardMonster[itm].setBehavior(monsterBehavior::moving);
			}
		}

		//regarde si il y a collision avec une slime devant
		for (list<behavioredMonster>::iterator itm2 = _boardMonster.begin(); itm2 != _boardMonster.end(); itm2++) {

			if (_boardMonster[itm2].getCellY() == _boardMonster[itm].getCellY() &&
				_boardMonster[itm2].getCellX() == _boardMonster[itm].getCellX() - 1) {
				_boardMonster[itm].setBehavior(monsterBehavior::idleM);
					break;
			}

		}
		//regarde si veut se deplacer
		if (_boardMonster[itm].getBehavior() == monsterBehavior::moving) {

			
			_boardMonster[itm].move();
		}
		//si on veut attaquer
		else if (_boardMonster[itm].getBehavior() == monsterBehavior::attackM) {

			//cherche le entity qui est devant moi
			for (list<behavioredEntity>::iterator it = _boardEntities.begin(); it != _boardEntities.end(); it++) {
				if (_boardEntities[it].getCellY() == _boardMonster[itm].getCellY() &&
					_boardEntities[it].getCellX() == _boardMonster[itm].getCellX() - 1)
				{
					_boardMonster[itm].attack(_boardEntities[it]);

				}
			}
		}

	}
}

gameStates entityManager::currentWaveStates()
{
	if (_boardMonster.empty()) {
		return gameStates::prep;
	}
	else if (_boardEntities.empty()) {
		return gameStates::prep;
	}
	else {
		return gameStates::wave;
	}
}

int entityManager::leakingMonster()
{
	int hploss = 0;

	for (list<behavioredMonster>::iterator itm = _boardMonster.begin(); itm != _boardMonster.end(); itm++) {

		if (_boardMonster[itm].getCellX() == 0) {
			hploss += (_boardMonster[itm].getID() + 1);
			_boardMonster[itm].leaked();

		}
	}
	cleanLeakers();

	return hploss;
}




