/*
 * Author:		Étienne Ménard
 * Date:		08/12/2020
 * File:		grid.h
 * Description:	Grille sur laquelle les troops et mobs vont être positionnés et vont bouger
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "Resources/include/map.hpp"

using namespace sf;

struct cell {
    int cellX;
    int cellY;
    bool occupied;
    Sprite sprite;
};

class grid
{
private:
    gameDataRef _data;
    mapp<cell> _grid;

    bool _gridToggle;   // if the grid is on or off

    void initGrid();

public:
    grid(gameDataRef data);
    void drawGrid()const;
    void toggleGrid();  // toggles the grid on and off

    bool isOccupied(int cellX, int cellY)const; // retourne si la cellule est occupée
    void setOccupied(int cellX, int cellY);

    int xPosScreen(int cellX)const;  // retourne la valeur x du coin haut gauche de la cellule en paramètre
    int yPosScreen(int cellY)const;  // retourne la valeur y du coin haut gauche de la cellule en paramètre

    cell& getCell(gameDataRef data)const;
};