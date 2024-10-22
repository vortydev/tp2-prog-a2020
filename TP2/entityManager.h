/*
 * Author:		�tienne M�nard
 * Date:		13/12/2020
 * File:		entityManager.h
 * Description:	Fichier m�re contenant les entities de r�f�rence, la liste des entities sur la grid et les shop units
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cassert>
#include <fstream>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "grid.h"
#include "behavioredEntity.h"
#include "behavioredMonster.h"

#include "Resources/include/vecteur.hpp"
#include "Resources/include/list.hpp"

using namespace sf;
using namespace std;

class entityManager
{
private:
    gameDataRef _data;

    ifstream _entityList;
    vecteur<behavioredEntity> _refEntities;
    vecteur<behavioredMonster> _refMonster;

    vecteur<behavioredEntity> _shopUnits;
    vecteur<cell> _shopUnitsCells;

    list<behavioredEntity> _boardEntities;
    list<behavioredMonster> _boardMonster;

public:
    entityManager(gameDataRef data);

    void loadRefEntities();             // intialise et remplis le vecteur avec les entities dans une liste
    void loadRefMonster();              //initialise et remplis un vecteur avec les monstres
    const behavioredEntity& getRefEntity(int id); // retourne l'entity avec l'id en param�tre
    const behavioredMonster& getRefMonster(int id);

    void loadShopUnits();       // initialise le vecteur de shop units
    void loadShopUnitsCells();
    void drawShopUnits(const int currency)const;

    cell& getShopUnitCell(gameDataRef data)const;
    void setSelected(cell& c);
    void setSelected(int cellX, cell& c);
    void unSelectCell(cell& c);

    const int boardEntitiesSize();
    const behavioredEntity& getBoardEntity(cell c);
    const bool isBoardUnitOnCell(cell c);
    const bool isBoardMobOnCell(cell c);
    void addUnitToBoard(const cell& cU, const cell& cP);
    void drawBoardEntities();
    int cleanBoard(grid* g);
    void cleanLeakers();
    void revitalizeEntities();

    void buyUnit(const cell& c, int& currency);
    void sellUnit(const cell& c, int& currency); 

    

    void update(float dt);
    void loadWave(int wave);

    void checkMonsterInRange();                             //scroll la liste de monstre pour chaque entit�
                                                            //change la behavior et inflige du degats

    void checkEntityInRange();                              //scroll la liste de entit� pour chaque monstre
                                                            //change la behavior et inflige du degats

    gameStates currentWaveStates();
    int leakingMonster();
    int massLeak();
};