/*
** EPITECH PROJECT, 2025
** player
** File description:
** The player class of wolf3d.
*/

#ifndef PLAYER_CLASS
    #define PLAYER_CLASS

    // Standard includes
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    // Custom includes
    #include "./../../../libs/classhandler/include/classhandler.h"

    // Defines
    #define PLAYER_DEFAULT_HEALTH 100
    #define PLAYER_DEFAULT_DMG 100
    #define PLAYER_DEFAULT_MOVE_SPEED 100
    #define PLAYER_DEFAULT_JUMP_POWER 100

// Typedefs

typedef enum player_state_e {
    PLAYER_IDLE,
    PLAYER_MOVING,
    PLAYER_SPRINTING,
    PLAYER_JUMPING,
} player_state_t;

typedef struct player_pos_s {
    float x;
    float y;
    float z;
} player_pos_t;

typedef struct player_s {

    player_pos_t pos;
    player_state_t state;

    uint16_t health;
    uint16_t dmg;

    float jump_power;
    float move_speed;

} player_t;

// Methods

/// GET methods
float player_getspeed(entity_t *entity);
float player_getjumppower(entity_t *entity);
uint16_t player_gethealth(entity_t *entity);
uint16_t player_getdmg(entity_t *entity);
player_state_t player_getstate(entity_t *entity);
player_pos_t player_getpos(entity_t *entity);

/// SET methods
size_t player_setdefault(entity_t *entity);
size_t player_setspeed(entity_t *entity, float value);
size_t player_setjumppower(entity_t *entity, float value);
size_t player_sethealth(entity_t *entity, uint16_t value);
size_t player_setdmg(entity_t *entity, uint16_t value);
size_t player_setstate(entity_t *entity, player_state_t state);
size_t player_setpos(entity_t *entity, player_pos_t *pos);

/// GAMEPLAY methods
size_t player_gpmovex(entity_t *entity, float value);
size_t player_gpmovey(entity_t *entity, float value);
size_t player_gpmovez(entity_t *entity, float value);

// les compliques pour plus tard
//size_t player_gpjump(const char *name);
//size_t player_gpattack(const char *name);
//size_t player_gpdie(const char *name);

#endif