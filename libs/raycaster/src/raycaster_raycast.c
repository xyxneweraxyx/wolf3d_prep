/*
** EPITECH PROJECT, 2025
** raycaster
** File description:
** A raycasting lib for wolf3d.
*/

#include "./../include/raycaster.h"
#include "./private.h"

static void ini_vals(raycast_t *raycast, ray_exec_t *data)
{
    data->map_x = str_len(raycast->origin.map[0]);
    data->map_y = 0;
    for (; raycast->origin.map[data->map_y]; data->map_y++);
    if (raycast->result)
        c_free(raycast->result, raycast->alloc);
    raycast->result = NULL;
    data->degree_begin = raycast->origin.degree - raycast->render.degree / 2;
    data->degree_end = raycast->origin.degree + raycast->render.degree / 2;
    data->map_cur_x = (int)raycast->origin.origin.x;
    data->map_cur_y = (int)raycast->origin.origin.y;
}

static void ini_dda(raycast_t *raycast, ray_exec_t *data)
{
    float cos_a = cosf(data->degree_modulo * DEG_TO_RAD);
    float sin_a = sinf(data->degree_modulo * DEG_TO_RAD);
    float frac_x = 0;
    float frac_y = 0;
    printf("angle %.2f\n", data->degree_modulo);

    data->dx = 0;
    data->dy = 0;
    data->dx = (cos_a >= 0) ? 1 : -1;
    data->dy = (sin_a >= 0) ? 1 : -1;
    data->delta_dist_x = (fabsf(cos_a) < 1e-3) ? -1 : fabsf(1 / cos_a); // On met juste a -1 pour skip
    data->delta_dist_y = (fabsf(sin_a) < 1e-3) ? -1 : fabsf(1 / sin_a);
    printf("delta %.2f %.2f\n", data->delta_dist_x, data->delta_dist_y);
    frac_x = raycast->origin.origin.x - floorf(raycast->origin.origin.x);
    frac_y = raycast->origin.origin.y - floorf(raycast->origin.origin.y);
    printf("frac %.2f %.2f\n", frac_x, frac_y);
    data->side_dist_x = (data->dx) ? (1 - frac_x) * data->delta_dist_x : frac_x * data->delta_dist_x;
    data->side_dist_y = (data->dy) ? (1 - frac_y) * data->delta_dist_y : frac_y * data->delta_dist_y;
    printf("side %.2f %.2f\n", data->side_dist_x, data->side_dist_y);
}

static bool dda_step(ray_exec_t *data)
{
    if (data->side_dist_x < data->side_dist_y) {
        data->min_dist = data->side_dist_x;
        data->side_dist_x += data->delta_dist_x;
        data->map_cur_x += data->dx;
        data->x = true;
    } else {
        data->min_dist = data->side_dist_y;
        data->side_dist_y += data->delta_dist_y;
        data->map_cur_y += data->dy;
        data->x = false;
    }
    printf("current x %d current y %d\n", data->map_cur_x, data->map_cur_y);
    if (data->map_cur_x <= 0 || data->map_cur_y <= 0 ||
        (size_t)data->map_cur_x >= data->map_x ||
        (size_t)data->map_cur_y >= data->map_y)
        return false;
    return true;
}

static size_t single_raycast(raycast_t *raycast, ray_exec_t *data)
{
    ini_dda(raycast, data);
    while (1) {
        if (!dda_step(data)) {
            printf("\n");
            return RAYCAST_SUCC;
        }
        if (raycast->origin.map[data->map_cur_y][data->map_cur_x]
            == raycast->origin.wall) {
            data->min_x = (size_t)data->map_cur_x;
            data->min_y = (size_t)data->map_cur_y;
            printf("hit (%zu, %zu) dist=%.2f side=%s\n\n",
                data->min_x, data->min_y, data->min_dist,
                data->x ? "X" : "Y");
            return RAYCAST_SUCC;
        }
    }
}

size_t raycast_raycast(raycast_t *raycast)
{
    ray_exec_t data;

    if (!raycast || !raycast->origin.map || !raycast->origin.map[0])
        return RAYCAST_FAIL;
    ini_vals(raycast, &data);
    for (float degree = data.degree_begin;
        degree <= data.degree_end + 90;
        degree += raycast->calculations.degree_add) {
        data.degree_modulo = (((int)degree + 360) % 360)
            + (degree - (int)degree);
        if (single_raycast(raycast, &data))
            return RAYCAST_FAIL;
    }
    return RAYCAST_SUCC;
}