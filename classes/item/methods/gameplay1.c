/*
** EPITECH PROJECT, 2025
** player
** File description:
** The item class of wolf3d.
*/

#include "./../include/item.h"

static void get_closest(item_t *data,
    float *closest, size_t *closest_id, float pos[3])
{
    float pos_item[3] = {0};
    float current = 0;

    for (size_t id = 0; id < data->current_amount; id++) {
        pos_item[0] = data->positions->x;
        pos_item[1] = data->positions->y;
        pos_item[2] = data->positions->z;
        current = distance_3d(pos_item, pos);
        if (current < (*closest)) {
            (*closest) = current;
            (*closest_id) = id;
        }
    }
}

size_t item_gpclosest(entity_t *item, float pos[3])
{
    float closest = __FLT_MAX__;
    size_t closest_id = 0;
    item_t *data = NULL;

    if (!item || !item->data)
        return (size_t)-1;
    data = item->data;
    get_closest(data, &closest, &closest_id, pos);
    data->closest_index = closest_id;
    return (size_t)0;
}

static bool is_facing(float pos1[3], float pos2[3], float angle)
{
    return true;
}

size_t item_gppickup(entity_t *entity, size_t index,
    float pos[3], float angle)
{
    item_t *item = NULL;
    float item_pos[3] = {0};

    if (!entity || !entity->data)
        return (size_t)0;
    item = (item_t *)entity->data;
    item_pos[0] = item->positions->x;
    item_pos[1] = item->positions->y;
    item_pos[2] = item->positions->z;
    if (distance_3d(item_pos, pos) > item->detection_radius)
        return (size_t)-1;
    if (!is_facing(item_pos, pos, angle))
        return (size_t)-1;
    // Delete the item from the position linked list!
    return (size_t)0;
}

size_t item_gpspawndelete(entity_t *entity)
{
    return (size_t)0;
}
