/*
 * Author:		�tienne M�nard
 * Date:		25/11/2020
 * File:		stateMachine.h
 * Description:	Contr�le les states du jeu.
 */

#pragma once
#include <memory>
#include <stack>
#include "state.hpp"

using namespace std;

typedef unique_ptr<state> stateRef; //un smartPointer de state

class stateMachine 
{
private:
	stack<stateRef> _states;	//pile de pointeur pour empiler les fen�tres du jeu
	stateRef _newState;			//la fen�tre active

	bool _isRemoving;			//flag pour savoir ce qui se passe ds la fen�tre
	bool _isAdding;
	bool _isReplacing;

public:
	void addState(stateRef newState, bool isReplacing = true);
	void removeState();

	void processStateChanges();
	stateRef& getActiveState(); //pas de const pour ce getteur, car il est setteur aussi
};