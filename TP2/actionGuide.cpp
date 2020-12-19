/*
 * Author:		Étienne Ménard
 * Date:		19/12/2020
 * File:		actionGuide.cpp
 * Description:	Défénitions des méthodes actionGuide.
 */

#include "actionGuide.h"

actionGuide::actionGuide(gameDataRef data) : _data(data)
{
    _helpToggled = false;   // load variables

    // load help sprite
    _helpSprite.setTexture(_data->assets.getTexture("action cell off"));
    _helpSprite.setPosition(SCREEN_WIDTH - 10 - _helpSprite.getGlobalBounds().width, 10);

    // load instructions
    loadInstructions();
}

// draw les éléments du actionGuide
void actionGuide::draw() const
{
    _data->window.draw(_helpSprite);
    // draw help text

    if (_helpToggled)   // only draw instuctions if help toggled
        drawInstructions();
}

void actionGuide::drawInstructions() const
{
    int offset = 0;
    for (int i = 0; i < _instructions.size(); i++) {
        if (_instructions[i].shown) {
            _instructions[i].instructionSprite.setPosition(SCREEN_WIDTH - 10 - _instructions[i].instructionSprite.getGlobalBounds().width, _helpSprite.getGlobalBounds().height + 20 + offset * _instructions[i].instructionSprite.getGlobalBounds().height);
            _instructions[i].instructionText.setPosition(SCREEN_WIDTH - 10 - _instructions[i].instructionSprite.getGlobalBounds().width / 2, 67 + _instructions[i].instructionSprite.getGlobalBounds().height / 2 + offset * _instructions[i].instructionSprite.getGlobalBounds().height);
            
            _data->window.draw(_instructions[i].instructionSprite); // draw la barre de bg
            _data->window.draw(_instructions[i].instructionText);   // draw le text

            offset++;
        }
    }
}

// retournes le help sprite
const Sprite& actionGuide::getHelpSprite()
{
    return _helpSprite;
}

// retournes si help is toggled
const bool actionGuide::isHelpToggled() const
{
    return _helpToggled;
}

// toggles le bool et modifie le sprite
void actionGuide::toggleHelp()
{
    // toggle le bool
    _helpToggled = !_helpToggled;

    // update le sprite
    if (_helpToggled)
        _helpSprite.setTexture(_data->assets.getTexture("action cell on"));
    else 
        _helpSprite.setTexture(_data->assets.getTexture("action cell off"));
}

// untoggles help s'il était toggled
void actionGuide::untoggleHelp()
{
    if (_helpToggled)
        toggleHelp();
}

// load le vecteur d'instructions
void actionGuide::loadInstructions()
{
    _instructionList.open(INSTRUCTION_LIST_FILEPATH);
    while (!_instructionList.eof()) {
        string s;
        getline(_instructionList, s);

        // instruction temp qui va être pushback dans le vecteur d'instructions
        instruction temp;

        temp.shown = false; // l'instruction sera activé seulement si nécessaire
        
        // set le sprite de l'instruction
        temp.instructionSprite.setTexture(_data->assets.getTexture("action instruction"));

        // set le text de l'instruction
        temp.instructionText.setFont(_data->assets.getFont("game font"));
        temp.instructionText.setString(s);
        temp.instructionText.setCharacterSize(16);
        temp.instructionText.setFillColor(Color::Black);
        temp.instructionText.setOrigin(temp.instructionText.getGlobalBounds().width / 2, temp.instructionText.getGlobalBounds().height / 2);
        
        _instructions.push_back(temp);
    }
}

void actionGuide::updateInstructionsShown(int prepPhase, bool confirmButton, bool cancelButton, bool unitSelected, bool placementSelected, int boardEntities)
{
    // reset toutes les instructions à false si elle était vraie
    for (int i = 0; i < _instructions.size(); i++) {
        if (_instructions[i].shown)
            _instructions[i].shown = false;
    }

    if (prepPhase == prepPhases::unitSelection || prepPhase == prepPhases::awaitingWave) {
        if (!unitSelected)
            _instructions[0].shown = true;
        else 
            _instructions[1].shown = true;

        if (!unitSelected && boardEntities != 0)
            _instructions[5].shown = true;
    }

    if (prepPhase == prepPhases::unitSelling) {
        if (placementSelected && boardEntities > 1)
            _instructions[6].shown = true;
    }
    
    if (unitSelected) {
        if (!placementSelected)
            _instructions[2].shown = true;
        else
            _instructions[3].shown = true;
    }

    if (confirmButton) {
        if (prepPhase == prepPhases::unitPlacement)
            _instructions[4].shown = true;
        else if (prepPhase == prepPhases::unitSelling)
            _instructions[7].shown = true;
        else if (prepPhase == prepPhases::awaitingWave)
            _instructions[8].shown = true;
    }
    
    if (cancelButton)
        _instructions[9].shown = true;
}