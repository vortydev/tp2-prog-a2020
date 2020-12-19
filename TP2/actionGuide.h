/*
 * Author:		Étienne Ménard
 * Date:		19/12/2020
 * File:		actionGuide.h
 * Description:	Guide des actions possibles.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "DEFINITIONS.hpp"
#include "game.h"
#include "Resources/include/vecteur.hpp"

using namespace sf;
using namespace std;

struct instruction {
    bool shown;
    Text instructionText;
    Sprite instructionSprite;
};

class actionGuide
{
private:
    gameDataRef _data;  // your usual game data
    Clock _clock;

    ifstream _instructionList;  // fichier duquel on a la liste des instructions
    vecteur<instruction> _instructions; // vecteur avec toutes les possibles instructions

    bool _helpToggled;   // bool if the help is shown or not
    Sprite _helpSprite;    // Sprite that will be clicked to show help
    Text _helpText;      // Just the text for the "?"

public:
    actionGuide(gameDataRef data);
    void draw()const;
    void drawInstructions()const;

    // help toggling
    const Sprite& getHelpSprite();   // retournes le sprite d'aide
    const bool isHelpToggled()const;
    void toggleHelp();
    void untoggleHelp();

    void loadInstructions();
    void updateInstructionsShown(int prepPhase, bool confirmButton, bool cancelButton, bool unitSelected, bool placementSelected, int boardEntities);
};