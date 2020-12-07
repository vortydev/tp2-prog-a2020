/*
 * Author:		�tienne M�nard
 * Date:		25/11/2020
 * File:		state.hpp
 * Description:	Frame de base d'un state. Constitue le coeur de chaque �tat (fen�tre) du jeu.
 */

#pragma once

class state
{
public:
	virtual void init() = 0;					//init de state
	virtual void handleInput() = 0;				//tous les input de la fen�tre
	virtual void update(float delta) = 0;		//update la fen�tre apr�s le input
	virtual void draw(float delta)const = 0;	//draw la fen�tre apr�s le update (delta est
												//la diff�rence de temps avec le frame rate)
	virtual void pause() {} 					//pause et resume le state
	virtual void resume() {}
};