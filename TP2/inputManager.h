/*
 * Author:		�tienne M�nard
 * Date:		26/11/2020
 * File:		inputManager.h
 * Description:	Contr�le les inputs du jeux.
 */

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class inputManager
{
public:
    bool isSpriteClicked(const Sprite& object, Mouse::Button button, RenderWindow& window);
    Vector2i getMousePosition(RenderWindow& window) const;
};