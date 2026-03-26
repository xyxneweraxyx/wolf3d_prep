/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** Callback connexion entry point.
*/

#include "./../../include/wolf3d.h"
#include "./callbacks.h"

static void attempt_move(wolf_t *wolf, entity_t *plr, float x, float z)
{
    player_t *data = (player_t *)plr->data;
    float margin = 0.1f;
    float next_x = data->pos.x + x;
    float next_z = data->pos.z + z;
    char wall = wolf->raycast->origin.wall;
    float check_x = next_x + (x >= 0 ? margin : -margin);
    float check_z = next_z + (z >= 0 ? margin : -margin);

    if (wolf->map[(int)data->pos.z][(int)check_x] != wall)
        player_gpmovex(plr, x);
    if (wolf->map[(int)check_z][(int)data->pos.x] != wall)
        player_gpmovez(plr, z);
}

static void movement(wolf_t *wolf, entity_t *plr)
{
    player_t *data = (player_t *)plr->data;
    float speed = data->move_speed / 100;
    float rot_speed = data->rot_speed / 100;

    if (sfKeyboard_isKeyPressed(sfKeyZ))
        attempt_move(wolf, plr,
            cosf(data->rotation * DEG_TO_RAD) * speed,
            sinf(data->rotation * DEG_TO_RAD) * speed);
    if (sfKeyboard_isKeyPressed(sfKeyS))
        attempt_move(wolf, plr,
            -1 * cosf(data->rotation * DEG_TO_RAD) * speed,
            -1 * sinf(data->rotation * DEG_TO_RAD) * speed);
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        player_addrotation(plr, rot_speed * -1);
    if (sfKeyboard_isKeyPressed(sfKeyD))
        player_addrotation(plr, rot_speed);
}

static void jump(entity_t *entity)
{
    player_t *data = entity->data;

    if (!data->jmp_strength) {
        if (sfKeyboard_isKeyPressed(sfKeySpace))
            player_gpjump(entity);
    }
    data->jmp_gravity += data->gravity / 100;
    data->jmp_strength -= data->jmp_gravity;
    if (data->pos.y + data->jmp_strength < 0) {
        data->pos.y = 0;
        data->jmp_strength = 0;
        data->jmp_gravity = 0;
        return;
    }
    data->pos.y += data->jmp_strength;
}

static size_t keyboard(setfml_t *setfml, void *userdata)
{
    wolf_t *wolf = (wolf_t *)setfml->userdata;
    entity_t *entity = classhandler_fetchentityname(wolf->classhandler, CLASS_PLAYERS, NULL);
    player_t *player = (player_t *)entity->data;

    if (!player)
        return (size_t)SETFML_FAIL;
    movement(wolf, entity);
    jump(entity);
    return (size_t)SETFML_SUCC;
}

int connect_keyboard(wolf_t *wolf)
{
    setfml_add(wolf->setfml, &(setfml_func_comp_t){NULL, &keyboard},
        "kb_directions", LOOP_DATA);
    return WOLF_SUCC;
}