/*
 * Author:		Étienne Ménard
 * Date:		26/11/2020
 * File:		DEFINITIONS.hpp
 * Description:	Fichier contenant les constantes nécessaires pour le projet. Réutilisable pour des projets ultérieurs.
 */

#pragma once
#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024

 // gameState
enum gameStates {
    ready,
    prep,
    wave,
    gameOver
};