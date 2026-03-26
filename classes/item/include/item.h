/*
** EPITECH PROJECT, 2025
** player
** File description:
** The player class of wolf3d.
*/

#ifndef ITEM_CLASS
    #define ITEM_CLASS

    // Standard includes
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <SFML/Graphics.h>

    // Custom includes
    #include "./../../../libs/classhandler/include/classhandler.h"

    // Defines
    #define DEFAULT_MAX_ITEM 25
    #define DEFAULT_DETECTION_RADIUS 0.75
    #define DEFAULT_DETECTION_ANGLE 90

// Typedefs

typedef enum item_state_e {
    ITEM_HIDDEN,
    ITEM_DRAWN,
} item_state_t;

typedef struct item_pos_s {
    float x;
    float y;
} item_pos_t;

typedef struct item_s {

    sfSprite *sprite;
    sfTexture *texture;

    item_pos_t *positions;
    item_state_t state;

    float detection_radius;
    float detection_angle;

    bool is_in_radius;
    size_t closest_index;

} item_t;

// Methods

/// GET methods
sfSprite *item_getsprite(entity_t *entity);
sfTexture *item_gettexture(entity_t *entity);
item_state_t item_getstate(entity_t *entity);
float item_getdetectionradius(entity_t *entity);
float item_getdetectionangle(entity_t *entity);

/// SET methods
size_t item_setsprite(entity_t *entity, sfSprite *sprite);
size_t item_settexture(entity_t *entity, sfTexture *texture);
size_t item_setstate(entity_t *entity, item_state_t state);
size_t item_setdetectionradius(entity_t *entity, float radius);
size_t item_setdetectionangle(entity_t *entity, float angle);

/// GAMEPLAY methods
size_t item_gpclosest(entity_t *entity); // Also sets is_in_radius
size_t item_gppickup(entity_t *entity, size_t index); // with sanity checks

#endif