/*
 * Author:		Étienne Ménard
 * Date:		26/11/2020
 * File:		DEFINITIONS.hpp
 * Description:	Fichier contenant les constantes nécessaires pour le projet. Réutilisable pour des projets ultérieurs.
 */

#pragma once
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// gameState
enum gameStates {
    ready,
    prep,
    wave,
    gameOver
};

// board elements
#define GAME_BACKGROUND_FILEPATH "Resources/res/game_bg.png"
#define GAME_PLAYER_ZONE_FILEPATH "Resources/res/game_player_zone.png"
#define GAME_ENEMY_ZONE_FILEPATH "Resources/res/game_enemy_zone.png"
#define GAME_MENU_BODY_FILEPATH "Resources/res/game_menu_body.png"