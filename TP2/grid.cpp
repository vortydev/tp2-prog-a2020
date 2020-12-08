/*
 * Author:		Étienne Ménard
 * Date:		08/12/2020
 * File:		grid.cpp
 * Description:	Définitions des méthodes de grid.
 */

#include "grid.h"

grid::grid(gameDataRef data) : _data(data) 
{
    initGrid();
}

void grid::initGrid()
{
    _grid.resize(5, 10);    // sets grid's size
    _gridToggle = true;     // sets if the grid is visible or not

    // loads chaque cellule de la grid
    for (int i = 0; i < _grid.nbLine(); i++)
    {
        for (int j = 0; j < _grid.nbCol(); j++)
        {
            _grid[i][j].cellX = j;
            _grid[i][j].cellY = i;
            _grid[i][j].occupied = false;

            _grid[i][j].sprite.setTexture(_data->assets.getTexture("grid cell white"));
            _grid[i][j].sprite.setPosition(80 * j + 240, 80 * i + 50);
        }
    }
}

// draw toutes les cases de la grid
void grid::drawGrid() const
{
    for (int i = 0; i < _grid.nbLine(); i++) 
    {
        for (int j = 0; j < _grid.nbCol(); j++)
        {
            _data->window.draw(_grid[i][j].sprite);
        }
    }
}

// toggles the grid on and off
void grid::toggleGrid()
{
    _gridToggle = !_gridToggle; // flips the bool

    // sets the correct texture
    for (int i = 0; i < _grid.nbLine(); i++)
    {
        for (int j = 0; j < _grid.nbCol(); j++)
        {
            if (_gridToggle)
                _grid[i][j].sprite.setTexture(_data->assets.getTexture("grid cell white"));
            else
                _grid[i][j].sprite.setTexture(_data->assets.getTexture("grid cell empty"));
        }
    }

}

// retourne si la cellule de la grid est occupée
bool grid::isOccupied(int cellX, int cellY) const
{
    return _grid[cellY][cellX].occupied;
}

void grid::setOccupied(int cellX, int cellY)
{
    _grid[cellY][cellX].occupied = !_grid[cellY][cellX].occupied;
}

// retourne la valeur x du coin haut gauche de la cellule en paramètre
int grid::xPosScreen(int cellX) const
{
    return 80 * cellX + 240;
}

// retourne la valeur y du coin haut gauche de la cellule en paramètre
int grid::yPosScreen(int cellY) const
{
    return 80 * cellY + 50;
}