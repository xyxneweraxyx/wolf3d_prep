/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** Main header file of wolf3d
*/

#ifndef WOLF3D_H
    #define WOLF3D_H

    // Standard includes
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <unistd.h>
    #include <math.h>

    // Custom includes
    #include "./../libs/c_alloc/c_alloc.h"
    #include "./../libs/linkedlist/linkedlist.h"
    #include "./../libs/str/str.h"
    #include "./../libs/buttonfml/buttonfml.h"
    #include "./../libs/setfml/setfml.h"
    #include "./../libs/raycaster/include/raycaster.h"
    #include "./../libs/classhandler/include/classhandler.h"

    // Classes
    #include "./../classes/player/include/player.h"
    #include "./../classes/enemy/include/enemy.h"

    // Return codes
    #define WOLF_SUCC 0
    #define WOLF_FAIL 84

    // Buffer lengths
    #define BUFF_LEN_NAME 32

    // Default parameter values
    #define PARAMS_DEFAULT_NAME "Jean marc" // jai que ca a foutre

    // Classes definition
    #define CLASS_PLAYERS "players"

    // Csfml assets
    #define SFML_TXT_WALL "./assets/textures/wall.jpg"

// Typedefs

typedef enum gamestate_e {
    GAME_MENU,
    GAME_SETTINGS,
    GAME_PLAY,
    GAME_PAUSED,
} gamestate_t;

typedef struct wolf_s {
    c_alloc_t *alloc;
    classhandler_t *classhandler;
    setfml_t *setfml;
    buttonfml_t *buttonfml;
    char **map;
    gamestate_t state;
    params_t params;
    raycast_t *raycast;
} wolf_t;

// Functions

int ini_csfml_env(wolf_t *wolf);
int connect_callbacks(wolf_t *wolf);
int destroy_return_int(int RET_CODE, wolf_t *wolf);
void *destroy_return_null(wolf_t *wolf);
int create_classes(wolf_t *wolf);

#endif