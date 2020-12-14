/*
 * Author:		Étienne Ménard
 * Date:		26/11/2020
 * File:		DEFINITIONS.hpp
 * Description:	Fichier contenant les constantes nécessaires pour le projet. Réutilisable pour des projets ultérieurs.
 */

#pragma once
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define GAME_FONT_FILEPATH "Resources/fonts/Planetesimal-Regular.ttf"
#define ENTITY_LIST_FILEPATH "Resources/entityList.txt"

// gameState
enum gameStates {
    loading,
    prep,
    wave,
    gameOver
};

// board elements
#define GAME_BACKGROUND_FILEPATH "Resources/res/game_bg.png"
#define GAME_PLAYER_ZONE_FILEPATH "Resources/res/game_player_zone.png"
#define GAME_ENEMY_ZONE_FILEPATH "Resources/res/game_enemy_zone.png"

// grid
#define GRID_CELL_EMPTY_FILEPATH "Resources/res/grid_cell_empty.png"
#define GRID_CELL_WHITE_FILEPATH "Resources/res/grid_cell_white.png"
#define GRID_CELL_GREY_FILEPATH "Resources/res/grid_cell_grey.png"
#define GRID_CELL_RED_FILEPATH "Resources/res/grid_cell_red.png"
#define GRID_CELL_GREEN_FILEPATH "Resources/res/grid_cell_green.png"
#define GRID_CELL_BLUE_FILEPATH "Resources/res/grid_cell_blue.png"

// game menu
enum prepPhases {
    unitSelection,
    unitPlacement,
    unitTransaction,
    awaitingWave,
    hold
};

#define GAME_MENU_BODY_FILEPATH "Resources/res/game_menu_body.png"
#define GAME_MENU_BUTTON_FILEPATH "Resources/res/game_menu_button.png"