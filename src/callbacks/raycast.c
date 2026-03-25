/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** Raycast callbacks to setfml.
*/

#include "./../../include/wolf3d.h"
#include "./callbacks.h"

static void modify_raycast_data(raycast_t *ray, player_t *player)
{
    ray->origin.degree = player->rotation;
    ray->origin.origin.x = player->pos.x;
    ray->origin.origin.y = player->pos.z;
    ray->render.height = player->pos.y;
}

static size_t raycast_function(setfml_t *setfml, void *userdata)
{
    wolf_t *wolf = (wolf_t *)setfml->userdata;
    raycast_t *ray = wolf->raycast;
    entity_t *entity = classhandler_fetchentityname(wolf->classhandler, CLASS_PLAYERS, NULL);
    player_t *player = (player_t *)entity->data;

    modify_raycast_data(ray, player);
    raycast_raycast(ray, setfml);
    return SETFML_SUCC;
}

static void shader(sfRectangleShape *col, col_data_t *data)
{
    int shade = (255 - data->distance * 30);
    shade = (shade < 0) ? 0 : shade;
    texture_t *texture = setfml_texturefromname(data->setfml, "wall", false);
    sfVector2u tex_size;

    sfRectangleShape_setFillColor(col, (sfColor){shade, shade, shade, 255});
    if (!texture)
        return;
    tex_size = sfTexture_getSize(texture->texture);
    sfRectangleShape_setTexture(col, texture->texture, sfFalse);
    sfRectangleShape_setTextureRect(col, (sfIntRect){
        (int)(data->face_x * tex_size.x), 0, 1, (int)tex_size.y});
}

int connect_raycasts(wolf_t *wolf)
{
    entity_t *entity = classhandler_fetchentityname(wolf->classhandler,
        CLASS_PLAYERS, NULL);
    player_t *plr = NULL;
    raycast_t *raycast = NULL;

    if (!entity || !entity->data)
        return WOLF_FAIL;
    plr = (player_t *)entity->data;
    raycast = raycast_create(wolf->map, &(ray_twod_t){plr->pos.x, plr->pos.z});
    if (!raycast)
        return WOLF_FAIL;
    raycast->modification = shader;
    wolf->raycast = raycast;
    setfml_add(wolf->setfml, &(setfml_func_comp_t){NULL, &raycast_function},
        "raycast", LOOP_DRAW);
    wolf->raycast = raycast;
    return WOLF_SUCC;
}