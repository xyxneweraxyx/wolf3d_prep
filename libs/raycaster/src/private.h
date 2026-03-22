/*
** EPITECH PROJECT, 2025
** raycaster
** File description:
** A raycasting lib for wolf3d.
*/

#ifndef RAYCAST_PRIVATE
    #define RAYCAST_PRIVATE

    #include "./../include/raycaster.h"

// Typedefs

typedef struct ray_exec_s {

    size_t map_x; // X size of the currently stored map.
    size_t map_y; // Y size of the currently stored map.

    float degree_begin; // The beginning point of the degrees for the raycast.
    float degree_end; // The end point of the degrees for the raycast.

    float degree_modulo; // The degrees with a modulo 360 applied.

    int8_t dx; // Step direction on x axis (-1 or 1).
    int8_t dy; // Step direction on y axis (-1 or 1).

    float delta_dist_x; // Distance along the ray between two consecutive vertical grid lines.
    float delta_dist_y; // Distance along the ray between two consecutive horizontal grid lines.
    float side_dist_x;  // Distance to the next vertical grid crossing.
    float side_dist_y;  // Distance to the next horizontal grid crossing.

    int map_cur_x; // X index of the cell currently being traversed.
    int map_cur_y; // Y index of the cell currently being traversed.

    float min_dist;  // Distance to the wall that was hit.
    size_t min_x;    // X index of the hit wall cell.
    size_t min_y;    // Y index of the hit wall cell.

    bool x; // If true, the wall was hit on an X side.

} ray_exec_t;

// Functions

/// Math functions
size_t number_in_range_f(float number, float base, float range);
size_t number_in_range_i(int number, int base, int range);

/// String functions
int str_len(const char *str);

#endif