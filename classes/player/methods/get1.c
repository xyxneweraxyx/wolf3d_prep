/*
** EPITECH PROJECT, 2025
** player
** File description:
** The player class of wolf3d.
*/

#include "./../include/player.h"

float player_getspeed(entity_t *entity)
{
    player_t *player = NULL;

    if (!entity ||
        !entity->class ||
        entity->class->byte_size != sizeof(player_t))
        return -1;
    player = (player_t *)entity->data;
    return player->move_speed;
}

float player_getjumppower(entity_t *entity)
{
    player_t *player = NULL;

    if (!entity ||
        !entity->class ||
        entity->class->byte_size != sizeof(player_t))
        return -1;
    player = (player_t *)entity->data;
    return player->jump_power;
}

uint16_t player_gethealth(entity_t *entity)
{
    player_t *player = NULL;

    if (!entity ||
        !entity->class ||
        entity->class->byte_size != sizeof(player_t))
        return (uint16_t)-1;
    player = (player_t *)entity->data;
    return player->health;
}

uint16_t player_getdmg(entity_t *entity)
{
    player_t *player = NULL;

    if (!entity ||
        !entity->class ||
        entity->class->byte_size != sizeof(player_t))
        return (uint16_t)-1;
    player = (player_t *)entity->data;
    return player->dmg;
}
