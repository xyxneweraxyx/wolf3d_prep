/*
** EPITECH PROJECT, 2025
** raycaster
** File description:
** A raycasting lib for wolf3d.
*/

#include "./../include/raycaster.h"
#include "./private.h"

static int ini_vals(raycast_t *raycast, ray_exec_t *data,
    sfRenderWindow *window)
{
    sfVector2u win_size = sfRenderWindow_getSize(window);

    data->screen_width = (float)win_size.x;
    data->screen_height = (float)win_size.y;
    data->degree_begin = raycast->origin.degree - raycast->render.degree / 2;
    data->degree_end = raycast->origin.degree + raycast->render.degree / 2;
    data->degree_step = raycast->render.degree / data->screen_width;
    data->map_x = str_len(raycast->origin.map[0]);
    for (; raycast->origin.map[data->map_y]; data->map_y++);
    return RAYCAST_SUCC;
}

static void ini_dda(raycast_t *raycast, ray_exec_t *data)
{
    float cos_a = cosf(data->degree_modulo * DEG_TO_RAD);
    float sin_a = sinf(data->degree_modulo * DEG_TO_RAD);
    float frac_x = 0;
    float frac_y = 0;

    data->map_cur_x = (int)raycast->origin.origin.x;
    data->map_cur_y = (int)raycast->origin.origin.y;
    data->dx = (cos_a >= 0) ? 1 : -1;
    data->dy = (sin_a >= 0) ? 1 : -1;
    data->delta_dist_x = (fabsf(cos_a) < 1e-3) ? FLT_MAX : fabsf(1 / cos_a);
    data->delta_dist_y = (fabsf(sin_a) < 1e-3) ? FLT_MAX : fabsf(1 / sin_a);
    frac_x = raycast->origin.origin.x - floorf(raycast->origin.origin.x);
    frac_y = raycast->origin.origin.y - floorf(raycast->origin.origin.y);
    data->dist_from_x = (data->dx > 0) ? (1 - frac_x) * data->delta_dist_x
        : frac_x * data->delta_dist_x;
    data->dist_from_y = (data->dy > 0) ? (1 - frac_y) * data->delta_dist_y
        : frac_y * data->delta_dist_y;
}

static bool dda_check_for_collision(ray_exec_t *data)
{
    if (data->dist_from_x < data->dist_from_y) {
        data->min_dist = data->dist_from_x;
        data->dist_from_x += data->delta_dist_x;
        data->map_cur_x += data->dx;
        data->x = true;
    } else {
        data->min_dist = data->dist_from_y;
        data->dist_from_y += data->delta_dist_y;
        data->map_cur_y += data->dy;
        data->x = false;
    }
    if (data->map_cur_x < 0 || data->map_cur_y < 0 ||
        (size_t)data->map_cur_x >= data->map_x ||
        (size_t)data->map_cur_y >= data->map_y)
        return false;
    return true;
}

static bool single_raycast(raycast_t *raycast, ray_exec_t *data)
{
    ini_dda(raycast, data);
    for (size_t i = 0; i < raycast->calculations.max_dist; i++) {
        if (!dda_check_for_collision(data))
            return false;
        if (raycast->origin.map[data->map_cur_y][data->map_cur_x]
            == raycast->origin.wall)
            return true;
    }
    return false;
}

static void draw_column(raycast_t *raycast, ray_exec_t *data,
    float col_x, setfml_t *setfml)
{
    float cam_angle = raycast->origin.degree * DEG_TO_RAD;
    float ray_angle = data->degree_modulo * DEG_TO_RAD;
    float perp_dist = data->min_dist * cosf(ray_angle - cam_angle);
    float fov = raycast->render.degree * DEG_TO_RAD;
    float proj_dist = (data->screen_height / 2.0f) / tanf(fov / 2.0f);
    float wall_height = (proj_dist / perp_dist) * raycast->render.wall_height;
    float col_y = (data->screen_height - wall_height) / 2.0f;
    sfRectangleShape *col = sfRectangleShape_create();

    if (!col)
        return;
    if (raycast->modification)
        raycast->modification(col, &(col_data_t){perp_dist, setfml, raycast});
    sfRectangleShape_setSize(col, (sfVector2f){1.0f, wall_height});
    sfRectangleShape_setPosition(col, (sfVector2f){col_x, col_y});
    sfRenderWindow_drawRectangleShape(setfml->window, col, NULL);
    sfRectangleShape_destroy(col);
}

size_t raycast_raycast(raycast_t *raycast, setfml_t *setfml)
{
    ray_exec_t data = {0};
    float col_x = 0;
    float degree = 0;

    if (!raycast || !raycast->origin.map ||
        !raycast->origin.map[0] || !setfml->window)
        return RAYCAST_FAIL;
    if (ini_vals(raycast, &data, setfml->window) == RAYCAST_FAIL)
        return RAYCAST_FAIL;
    degree = data.degree_begin;
    while (degree <= data.degree_end) {
        data.degree_modulo = (((int)degree + 360) % 360)
            + (degree - (int)degree);
        if (single_raycast(raycast, &data))
            draw_column(raycast, &data, col_x, setfml);
        degree += data.degree_step;
        col_x += 1;
    }
    return RAYCAST_SUCC;
}