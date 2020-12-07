/*
 * Author:		�tienne M�nard
 * Date:		25/11/2020
 * File:		stateMachine.cpp
 * Description:	D�f�nition des m�thodes de la stateMachine.
 */

#include "stateMachine.h"

void stateMachine::addState(stateRef newState, bool isReplacing)
{
	_isAdding = true;
	_isReplacing = isReplacing;
		
	_newState = move(newState);
}

void stateMachine::removeState()
{
	_isRemoving = true;
}

void stateMachine::processStateChanges()
{
	if (_isRemoving && !_states.empty())	//Si on retire et que la pile d��tat
	{										//n�est pas vide
		_states.pop();						//pop la pile pour enlever le dernier �tat
		if (!_states.empty())				//Si la pile d��tat en contient un autre,
			_states.top()->resume();		//on le resume (repart)
	}
	_isRemoving = false;

	if (_isAdding)							//Si on ajoute un �tat(ouvre une fen�tre)
	{
		if (!_states.empty())				//si la pile d��tat n�est pas vide
		{
			if (_isReplacing)				//si on modifie, on pop pour remettre
				_states.pop();				//pour mettre le newState modifi�
			else
				_states.top()->pause();		//sinon, on fait une pause du top
		}

		_states.push(move(_newState));		//ajouter le _newState
		_states.top()->init();				//init le top qui est le newState
		_isAdding = false;
	}
}

stateRef& stateMachine::getActiveState()
{
	return _states.top();
}