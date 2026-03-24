/*
** EPITECH PROJECT, 2025
** player
** File description:
** The player class of wolf3d.
*/

#include "./../include/player.h"

size_t player_setdefault(entity_t *entity)
{
    player_t *player = NULL;

    if (!entity ||
        !entity->class ||
        entity->class->byte_size != sizeof(player_t))
        return (size_t)-1;
    player = (player_t *)entity->data;
    player->health = PLAYER_DEFAULT_HEALTH;
    player->dmg = PLAYER_DEFAULT_DMG;
    player->move_speed = PLAYER_DEFAULT_MOVE_SPEED;
    player->jump_power = PLAYER_DEFAULT_JUMP_POWER;
    player->pos = (player_pos_t){0, 0, 0};
    player->state = PLAYER_IDLE;
    return (size_t)0;
}

size_t player_setspeed(entity_t *entity, float value)
{
    player_t *player = NULL;

    if (!entity ||
        !entity->class ||
        entity->class->byte_size != sizeof(player_t))
        return (size_t)-1;
    player = (player_t *)entity->data;
    player->move_speed = value;
    return (size_t)0;
}

size_t player_setjumppower(entity_t *entity, float value)
{
    player_t *player = NULL;

    if (!entity ||
        !entity->class ||
        entity->class->byte_size != sizeof(player_t))
        return (size_t)-1;
    player = (player_t *)entity->data;
    player->jump_power = value;
    return (size_t)0;
}

size_t player_sethealth(entity_t *entity, uint16_t value)
{
    player_t *player = NULL;

    if (!entity ||
        !entity->class ||
        entity->class->byte_size != sizeof(player_t))
        return (size_t)-1;
    player = (player_t *)entity->data;
    player->health = value;
    return (size_t)0;
}

size_t player_setdmg(entity_t *entity, uint16_t value)
{
    player_t *player = NULL;

    if (!entity ||
        !entity->class ||
        entity->class->byte_size != sizeof(player_t))
        return (size_t)-1;
    player = (player_t *)entity->data;
    player->dmg = value;
    return (size_t)0;
}

