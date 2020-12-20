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
#define INSTRUCTION_LIST_FILEPATH "Resources/instructionList.txt"

#define SPLASH_SLIME_ANIMATION_DURATION 1.0f
#define TITLE_ANIMATION_DELAY 1.0f
#define TITLE_ANIMATION_DURATION 2.0f
#define MAIN_MENU_BUTTON_FILEPATH "Resources/res/main_menu_button.png"

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
#define GRID_CELL_PINK_FILEPATH "Resources/res/grid_cell_pink.png"
#define GRID_CELL_RED_FILEPATH "Resources/res/grid_cell_red.png"
#define GRID_CELL_BLOOD_FILEPATH "Resources/res/grid_cell_blood.png"
#define GRID_CELL_YELLOW_FILEPATH "Resources/res/grid_cell_yellow.png"
#define GRID_CELL_MUSTARD_FILEPATH "Resources/res/grid_cell_mustard.png"
#define GRID_CELL_GREEN_FILEPATH "Resources/res/grid_cell_green.png"
#define GRID_CELL_BLUE_FILEPATH "Resources/res/grid_cell_blue.png"
enum selectColor {
    blue,
    yellow,
    mustard
};

// game menu
enum prepPhases {
    unitSelection,
    unitPlacement,
    unitTransaction,
    unitSelling,
    awaitingWave,
    hold
};

#define GAME_MENU_BODY_FILEPATH "Resources/res/game_menu_body.png"
#define GAME_MENU_BUTTON_FILEPATH "Resources/res/game_menu_button.png"
#define GAME_CURRENCY_FILEPATH "Resources/res/game_currency.png"

// action guide
#define GAME_ACTION_CELL_OFF "Resources/res/game_action_cell_off.png"
#define GAME_ACTION_CELL_ON "Resources/res/game_action_cell_on.png"
#define GAME_ACTION_INSTRUCTION "Resources/res/game_action_instruction.png"

enum characterBehavior {
    idle,
    chargeAttack,
    attack,
    postAttack,
    dead
};
enum monsterBehavior {
    moving,
    idleM,
    chargeAttackM,
    attackM,
    postAttackM,
    deadM
};
#define BEHAVIOR_CLOCK 1.0f