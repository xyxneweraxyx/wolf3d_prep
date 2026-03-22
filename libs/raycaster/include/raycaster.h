/*
** EPITECH PROJECT, 2025
** raycaster
** File description:
** A raycasting lib for wolf3d.
*/

#ifndef RAYCASTER
    #define RAYCASTER

    // Includes default libs
    #include <stdio.h>
    #include <stdlib.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include <limits.h>
    #include <float.h>
    #include <math.h>

    // Includes private libs
    #include "./../../c_alloc/c_alloc.h"

    // Defines
    #define RAYCAST_SUCC 0
    #define RAYCAST_FAIL -1
    #define EMPTY_VERTEX -1

    // Hardcoded values
    #define PI 3.141592
    #define DEG_TO_RAD PI / 180

// Typedefs

typedef struct ray_threed_s {
    float x; // Component X.
    float y; // Component Y.
    float z; // Component Z.
} ray_threed_t;

typedef struct ray_twod_s {
    float x; // Component X.
    float y; // Component Y.
} ray_twod_t;

typedef struct shape_s {

    /*
    The four vertices that compose the shape.
    Stored in a clockwise order, from the top-left corner.
    */
    ray_threed_t vertices[4];

} shape_t;

typedef struct ray_render_s {

    /*
    Height of the render, in pixels.
    Defaults to 0, the middle of the screen will be used.
    */
    int16_t height;

    /*
    The degrees visible in the raycast.
    Defaults to 70.
    */
    uint8_t degree;

    /*
    Distance factor applied to the height of the raycast draw.
    Defaults to 0.
    */
    float distance;

} ray_render_t;

typedef struct ray_origin_s {

    /*
    Map used in the raycast. The map should contain the "walls" character.
    */
    char **map;

    /*
    The origin point of the raycast. This point should be expressed in map size.
    For example, {3.5, 4.5} will be considered as an origin in map[4][3].
    */
    ray_twod_t origin;

    /*
    Degree of the direct line of sight of the raycast.
    "degrees" in ray_result_t will base itself on this value.
    */
    float degree;

    /*
    The character in "map" to be considered as a wall.
    */
    char wall;

} ray_origin_t;

typedef struct ray_calc_s {

    /*
    The amount to add in the degrees loop over a single iteration.
    An amount close to 0 will give a more precise raycast but will take longer.
    Defaults to 1.
    */
    float degree_add;

} ray_calc_t;

typedef struct raycast_s {

    /*
    The c_alloc object used for allocations during the raycast's existence.
    */
    c_alloc_t *alloc;

    /*
    An array of shapes, terminated by NULL;
    Each "vertices" contains the coordinates of the four vertices to draw.
    The  array is NULL during the calculations. Allocations are automatic.
    */
    shape_t *result;

    /*
    Rendering options of the raycast.
    */
    ray_render_t render;

    /*
    Origin data of the raycast.
    */
    ray_origin_t origin;

    /*
    Calculation data of the raycast.
    */
    ray_calc_t calculations;

} raycast_t;

// Functions

/*
Creates a raycast_t object filled with default parameters.
The map must be null-terminated.
Returns the object on success, or NULL on fail.
*/
raycast_t *raycast_create(char **map, ray_twod_t origin);

/*
Destroys a raycast_t object.
*/
void raycast_destroy(raycast_t *raycast);

/*
Performs a raycast based on the parameters of raycast.
On success, stores the results in raycast->result and returns RAYCAST_SUCC.
On fail, returns RAYCAST_FAIL.
*/
size_t raycast_raycast(raycast_t *raycast);

#endif