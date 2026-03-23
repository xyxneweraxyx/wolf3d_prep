/*
** EPITECH PROJECT, 2025
** raycaster
** File description:
** A raycasting lib for wolf3d.
*/

#include "./../include/raycaster.h"
#include "./private.h"

static int ini_vals(raycast_t *raycast, ray_exec_t *data)
{
    float ray_amount = 0;

    data->degree_begin = raycast->origin.degree - raycast->render.degree / 2;
    data->degree_end = raycast->origin.degree + raycast->render.degree / 2;
    data->map_x = str_len(raycast->origin.map[0]);
    data->map_y = 0;
    data->written_shapes = 0;
    ray_amount = (data->degree_end - data->degree_begin)
        / raycast->calculations.degree_add;
    for (; raycast->origin.map[data->map_y]; data->map_y++);
    if (raycast->result)
        c_free(raycast->result, raycast->alloc);
    raycast->result = c_alloc(sizeof(shape_t),
        (int)(ray_amount) + 1, raycast->alloc);
    if (!raycast->result)
        return RAYCAST_FAIL;
    for (int i = 0; i <= (int)ray_amount + 1; i++)
        raycast->result[i].dist = -1;
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
    data->dx = 0;
    data->dy = 0;
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

static void store_new_shape(raycast_t *raycast, ray_exec_t *data)
{
    float side_x;
    float side_z;
    float height = raycast->calculations.height;
    shape_t *shape = &raycast->result[data->written_shapes];

    if (data->x) {
        side_x = (data->dx < 0) ? data->map_cur_x + 1 : data->map_cur_x;
        side_z = data->map_cur_y;
        shape->vertices[0] = (ray_threed_t){side_x, height + 1, side_z};
        shape->vertices[1] = (ray_threed_t){side_x, height + 1, side_z + 1};
        shape->vertices[2] = (ray_threed_t){side_x, height, side_z + 1};
        shape->vertices[3] = (ray_threed_t){side_x, height, side_z};
    } else {
        side_x = data->map_cur_x;
        side_z = (data->dy < 0) ? data->map_cur_y + 1 : data->map_cur_y;
        shape->vertices[0] = (ray_threed_t){side_x, height + 1, side_z};
        shape->vertices[1] = (ray_threed_t){side_x + 1, height + 1, side_z};
        shape->vertices[2] = (ray_threed_t){side_x + 1, height, side_z};
        shape->vertices[3] = (ray_threed_t){side_x, height, side_z};
    }
    shape->dist = data->min_dist;
}

static size_t single_raycast(raycast_t *raycast, ray_exec_t *data)
{
    ini_dda(raycast, data);
    for (size_t i = 0; i < raycast->calculations.max_dist; i++) {
        if (!dda_check_for_collision(data))
            return RAYCAST_SUCC;
        if (raycast->origin.map[data->map_cur_y][data->map_cur_x]
            == raycast->origin.wall) {
            data->min_x = (size_t)data->map_cur_x;
            data->min_y = (size_t)data->map_cur_y;
            store_new_shape(raycast, data);
            data->written_shapes++;
            return RAYCAST_SUCC;
        }
    }
    store_new_shape(raycast, data);
    data->written_shapes++;
    return RAYCAST_SUCC;
}

static int compare_shapes(const void *a, const void *b)
{
    float shape_a = ((shape_t *)a)->dist;
    float shape_b = ((shape_t *)b)->dist;

    if (shape_a < shape_b)
        return 1;
    if (shape_a > shape_b)
        return -1;
    return 0;
}

size_t raycast_raycast(raycast_t *raycast)
{
    ray_exec_t data;

    if (!raycast || !raycast->origin.map || !raycast->origin.map[0])
        return RAYCAST_FAIL;
    if (ini_vals(raycast, &data) == RAYCAST_FAIL)
        return RAYCAST_FAIL;
    for (float degree = data.degree_begin;
        degree <= data.degree_end;
        degree += raycast->calculations.degree_add) {
        data.degree_modulo = (((int)degree + 360) % 360)
            + (degree - (int)degree);
        if (single_raycast(raycast, &data))
            return RAYCAST_FAIL;
    }
    qsort(raycast->result, data.written_shapes,
        sizeof(shape_t), compare_shapes);
    return RAYCAST_SUCC;
}