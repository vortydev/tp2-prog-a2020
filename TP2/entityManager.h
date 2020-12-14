/*
 * Author:		Étienne Ménard
 * Date:		13/12/2020
 * File:		entityManager.h
 * Description:	Fichier mère contenant les entities de référence, la liste des entities sur la grid et les shop units
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cassert>
#include <fstream>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "grid.h"
#include "entity.h"

#include "Resources/include/vecteur.hpp"
#include "Resources/include/list.hpp"

using namespace sf;
using namespace std;

class entityManager
{
private:
    //struct entityVisualizer // to do

    gameDataRef _data;

    ifstream _entityList;
    vecteur<entity> _refEntities;

    vecteur<entity> _shopUnits;
    vecteur<cell> _shopUnitsCells;

    list<entity> _boardEntities;

public:
    entityManager(gameDataRef data);

    void loadRefEntities();             // intialise et remplis le vecteur avec les entities dans une liste
    const entity& getRefEntity(int id); // retourne l'entity avec l'id en paramètre

    void loadShopUnits();       // initialise le vecteur de shop units
    void loadShopUnitsCells();
    void drawShopUnits(const int currency)const;

    cell& getShopUnitCell(gameDataRef data)const;
    void setSelected(cell& c);
    void setSelected(int cellX, cell& c);
    void unSelectCell(cell& c);

    const int boardEntitiesSize();
    void addUnitToBoard(const cell& cU, const cell& cP);
    void unitTransaction(const cell& c, int& currency);
    void drawBoardEntities();
};