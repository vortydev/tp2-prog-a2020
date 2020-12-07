/*
 * Author:		Étienne Ménard
 * Date:		26/11/2020
 * File:		assetManager.h
 * Description:	Contrôle les assets du jeux.
 */

#pragma once
#include <map>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class assetManager
{
private:
    map<string, Texture> _textures;     //combine le nom de la texture à la Texture sfml
    map<string, Font> _fonts;           //combine le nom de la font à la Font sfml

public:
    void loadTexture(string name, string fileName);
    Texture& getTexture(string name);   //pas de const pour ce getteur, car setteur aussi

    void loadFont(string name, string fileName);
    Font& getFont(string name);         //pas de const pour ce getteur, car setteur aussi
};