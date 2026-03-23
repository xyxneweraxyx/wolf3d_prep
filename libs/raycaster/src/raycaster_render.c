/*
** EPITECH PROJECT, 2025
** raycaster
** File description:
** A rendering lib for wolf3d.
*/

#include "./../include/raycaster.h"
#include "./private.h"

static void ini_render_vals(raycast_t *raycast,
    ray_render_exec_t *data, sfRenderWindow *window)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    float cam_angle = raycast->origin.degree * DEG_TO_RAD;
    float fov = raycast->render.degree * DEG_TO_RAD;

    data->screen_width = (float)window_size.x;
    data->screen_height = (float)window_size.y;
    data->cam_x = raycast->origin.origin.x;
    data->cam_z = raycast->origin.origin.y;
    data->cam_height = raycast->calculations.height + 0.5f;
    data->cam_cos = cosf(cam_angle);
    data->cam_sin = sinf(cam_angle);
    data->proj_dist = (data->screen_width / 2.0f) / tanf(fov / 2.0f);
}

static sfVector2f project_vertex(ray_render_exec_t *data, ray_threed_t vertex)
{
    float relative_x = vertex.x - data->cam_x;
    float relative_z = vertex.z - data->cam_z;
    float horizontal = relative_x * (-data->cam_sin)
        + relative_z * data->cam_cos;
    float depth = relative_x * data->cam_cos + relative_z * data->cam_sin;
    float screen_x = data->screen_width / 2.0f
        + (horizontal / depth) * data->proj_dist;
    float screen_y = data->screen_height / 2.0f
        - ((vertex.y - data->cam_height) / depth) * data->proj_dist;

    return (sfVector2f){screen_x, screen_y};
}

static bool shape_is_visible(ray_render_exec_t *data, shape_t *shape)
{
    float relative_x = 0;
    float relative_z = 0;
    float depth = 0;

    for (int i = 0; i < 4; i++) {
        relative_x = shape->vertices[i].x - data->cam_x;
        relative_z = shape->vertices[i].z - data->cam_z;
        depth = relative_x * data->cam_cos + relative_z * data->cam_sin;
        if (depth > 0.001f)
            return true;
    }
    return false;
}

static void draw_shape(ray_render_exec_t *data,
    shape_t *shape, sfRenderWindow *window)
{
    sfConvexShape *convex = sfConvexShape_create();

    if (!convex)
        return;
    sfConvexShape_setPointCount(convex, 4);
    sfConvexShape_setFillColor(convex, sfWhite);
    for (int i = 0; i < 4; i++)
        sfConvexShape_setPoint(convex, i,
            project_vertex(data, shape->vertices[i]));
    sfRenderWindow_drawConvexShape(window, convex, NULL);
    sfConvexShape_destroy(convex);
}

void raycast_render(raycast_t *raycast, sfRenderWindow *window)
{
    ray_render_exec_t data = {0};

    if (!raycast || !raycast->result || !window)
        return;
    ini_render_vals(raycast, &data, window);
    for (int i = 0; raycast->result[i].dist >= 0; i++) {
        if (!shape_is_visible(&data, &raycast->result[i]))
            continue;
        draw_shape(&data, &raycast->result[i], window);
    }
}