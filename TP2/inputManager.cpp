/*
 * Author:		�tienne M�nard
 * Date:		26/11/2020
 * File:		inputManager.cpp
 * Description:	D�f�nition des m�thodes de l'inputManager.
 */

#include "inputManager.h"

//v�rifie si on a cliqu� sur le sprite de la fen�tre re�us en param�tre
bool inputManager::isSpriteClicked(const Sprite& object, Mouse::Button button, RenderWindow& window)
{
    if (Mouse::isButtonPressed(button))
    {
        IntRect tempRect(object.getPosition().x, object.getPosition().y,
            object.getGlobalBounds().width, object.getGlobalBounds().height);
        if (tempRect.contains(Mouse::getPosition(window)))
        {
            return true;
        }
    }
    return false;
}

//retourne la position de la souris de la fen�tre re�ue en param�tre
Vector2i inputManager::getMousePosition(RenderWindow& window) const
{
    return Mouse::getPosition(window);
}