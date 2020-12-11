/*
 * Author:		Étienne Ménard
 * Date:		08/12/2020
 * File:		grid.cpp
 * Description:	Définitions des méthodes de grid.
 */

#include "grid.h"

grid::grid(gameDataRef data) : _data(data) 
{
    _grid.resize(5, 10);    // sets grid's size
    _gridToggle = true;     // sets if the grid is visible or not

    // loads chaque cell de la grid
    for (int i = 0; i < _grid.nbLine(); i++)
    {
        for (int j = 0; j < _grid.nbCol(); j++)
        {
            _grid[i][j].cellX = j;
            _grid[i][j].cellY = i;
            _grid[i][j].occupied = false;
            _grid[i][j].selected = false;

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
            if (_gridToggle) {
                if (_grid[i][j].selected)
                    _grid[i][j].sprite.setTexture(_data->assets.getTexture("grid cell blue"));
                else if (_grid[i][j].occupied)
                    _grid[i][j].sprite.setTexture(_data->assets.getTexture("grid cell grey"));
                else
                    _grid[i][j].sprite.setTexture(_data->assets.getTexture("grid cell white"));
            }
            else
                _grid[i][j].sprite.setTexture(_data->assets.getTexture("grid cell empty"));
            
            _data->window.draw(_grid[i][j].sprite);
        }
    }
}

// toggles the grid on and off
void grid::toggleGrid()
{
    _gridToggle = !_gridToggle; // flips the bool
}

// retourne si la cell de la grid est occupée
bool grid::isOccupied(int cellX, int cellY) const
{
    return _grid[cellY][cellX].occupied;
}

// retourne si la cell de la grid est occupée
bool grid::isOccupied(const cell& c) const
{
    return c.occupied;
}

// toggles si la cell est occupée
void grid::setOccupied(int cellX, int cellY)
{
    _grid[cellY][cellX].occupied = !_grid[cellY][cellX].occupied;
}

void grid::setOccupied(cell& c)
{
    c.occupied = !c.occupied;
}

// retournes si la cell est selectionnée
bool grid::isSelected(const cell& c)const
{
    return c.selected;
}

bool grid::isSelected(int cellX, int cellY)const
{
    return _grid[cellY][cellX].selected;
}

void grid::setSelected(cell& c)
{
    c.selected = !c.selected;
}

// toggles si la cell est selectionnée
void grid::setSelected(int cellX, int cellY)
{   
    _grid[cellY][cellX].selected = !_grid[cellY][cellX].selected;
}

// toggles si la cell est selectionnée
void grid::setSelected(int cellX, int cellY, cell& c)
{
    // si la cell n'est pas déjà occupée
    if (!isOccupied(_grid[cellY][cellX])) {
        // if no cell has been selected yet
        if (c.cellX == -1) {
            c.cellX = cellX;
            c.cellY = cellY;
            setSelected(_grid[cellY][cellX]);
        }
        // if la cell est différente de celle déjà selectionnée
        else if (!(c.cellX == cellX && c.cellY == cellY)) {
            // deselects the previous cell
            setSelected(_grid[c.cellY][c.cellX]);

            // set the new cell's position
            c.cellX = cellX;
            c.cellY = cellY;

            // selects the new cell
            setSelected(_grid[cellY][cellX]);
        }
    }
}

// unselects the selected cell
void grid::unSelectCell(cell& c)
{
    setSelected(_grid[c.cellY][c.cellX]);
    c.cellX = -1;
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

cell& grid::getCell(gameDataRef data) const
{
    for (int i = 0; i < _grid.nbLine(); i++)
    {
        for (int j = 0; j < _grid.nbCol(); j++)
        {
            if (data->input.isSpriteClicked(_grid[i][j].sprite, Mouse::Left, data->window))
                return _grid[i][j];
        }
    }
}