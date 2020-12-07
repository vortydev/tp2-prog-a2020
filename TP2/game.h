/*
 * Author:		Étienne Ménard
 * Date:		26/11/2020
 * File:		game.h
 * Description:	Game loop.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <time.h>
#include "state.hpp"
#include "stateMachine.h"
#include "assetManager.h"
#include "inputManager.h"

using namespace sf;
using namespace std;

struct gameData {
    stateMachine machine;
    RenderWindow window;
    assetManager assets;
    inputManager input;
};
typedef shared_ptr<gameData> gameDataRef;

class game
{
private:
    const float dt = 1.0f / 60.0f; //temps pour chaque frame (60 frames par sec.)
    Clock _clock;
    gameDataRef _data; //Le pointeur sur la struct gameData

public:
    game(int width, int height, string title);
    void run();
};