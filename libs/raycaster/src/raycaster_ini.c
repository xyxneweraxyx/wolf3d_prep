/*
** EPITECH PROJECT, 2025
** raycaster
** File description:
** A raycasting lib for wolf3d.
*/

#include "./../include/raycaster.h"

// Bug notable : Si render.degree n'est pas un multiple de degree_add, alors la dernière exécution
// (supposément le dernier render tout a droite) est skip (a cause de la condition de la boucle principale). A fix potentiellement si problèmes.
raycast_t *raycast_create(char **map, ray_twod_t origin)
{
    c_alloc_t *alloc = c_ini((uint16_t)10);
    raycast_t *raycast = NULL;

    if (!alloc)
        return NULL;
    raycast = c_alloc(sizeof(raycast_t), 1, alloc);
    if (!raycast)
        return NULL;
    raycast->result = NULL;
    raycast->alloc = alloc;
    raycast->origin.degree = 120;
    raycast->origin.wall = '1';
    raycast->origin.map = map;
    raycast->origin.origin = origin;
    raycast->render.degree = 240;
    raycast->render.distance = 1;
    raycast->render.wall_height = 1;
    raycast->calculations.max_dist = 100;
    raycast->calculations.degree_add = 45;
    return raycast;
}

void raycast_destroy(raycast_t *raycast)
{
    if (!raycast || !raycast->alloc)
        return;
    c_delete(raycast->alloc, true);
}