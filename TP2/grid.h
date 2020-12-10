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
    bool selected;
    Sprite sprite;
};

class grid
{
private:
    gameDataRef _data;
    mapp<cell> _grid;

    bool _gridToggle;   // if the grid is on or off
    cell _selectedCell;

public:
    grid(gameDataRef data);
    void drawGrid()const;
    void toggleGrid();  // toggles the grid on and off

    bool isOccupied(int cellX, int cellY)const; // retourne si la cellule est occupée
    bool isOccupied(const cell& c)const;
    void setOccupied(int cellX, int cellY);
    void setOccupied(cell& c);

    void selectedCell();
    bool isSelected(int cellX, int cellY)const;
    bool isSelected(const cell& c)const;    // retourne si la cellule est sélectionnée
    void setSelected(int cellX, int cellY);
    void setSelected(cell& c);

    int xPosScreen(int cellX)const;  // retourne la valeur x du coin haut gauche de la cellule en paramètre
    int yPosScreen(int cellY)const;  // retourne la valeur y du coin haut gauche de la cellule en paramètre

    cell& getCell(gameDataRef data)const;
};