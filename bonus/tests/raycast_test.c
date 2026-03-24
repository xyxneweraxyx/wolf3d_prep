/*#include "./../libs/raycaster/include/raycaster.h"
#include "./../libs/setfml/setfml.h"

size_t raycast_1(setfml_t *setfml, void *userdata)
{
    raycast_t *ray = (raycast_t *)setfml->userdata;
    raycast_raycast(ray, setfml);
    return SETFML_SUCC;
}

void modif(sfRectangleShape *col, col_data_t *data)
{
    int shade = (255 - data->distance * 30);
    shade = (shade < 0) ? 0 : shade;
    texture_t *texture = setfml_texturefromname(data->setfml, "water", false);
    sfVector2u tex_size;

    sfRectangleShape_setFillColor(col, (sfColor){shade, shade, shade, 255});
    if (!texture)
        return;
    tex_size = sfTexture_getSize(texture->texture);
    sfRectangleShape_setTexture(col, texture->texture, sfFalse);
    sfRectangleShape_setTextureRect(col, (sfIntRect){
        (int)(data->face_x * tex_size.x), 0, 1, (int)tex_size.y});
}

size_t handle_keys(setfml_t *setfml, void *userdata)
{
    raycast_t *ray = (raycast_t *)setfml->userdata;
    float speed = 0.02f;
    float rot_speed = 0.5f;

    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        ray->origin.origin.x += cosf(ray->origin.degree * DEG_TO_RAD) * speed;
        ray->origin.origin.y += sinf(ray->origin.degree * DEG_TO_RAD) * speed;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        ray->origin.origin.x -= cosf(ray->origin.degree * DEG_TO_RAD) * speed;
        ray->origin.origin.y -= sinf(ray->origin.degree * DEG_TO_RAD) * speed;
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        ray->origin.degree -= rot_speed;
    if (sfKeyboard_isKeyPressed(sfKeyD))
        ray->origin.degree += rot_speed;
    return SETFML_SUCC;
}

char **create_map(void)
{
    const char *rows[] = {
        "111111111111111111111111111111",
        "100000000000000000000000000001",
        "100000000000000000000000000001",
        "100011110000000001111000000001",
        "100010000000000000001000000001",
        "100010001111111100001000000001",
        "100010001000000100001000000001",
        "100010001000000100001111110001",
        "100000001000000100000000000001",
        "100000001000000100000000000001",
        "100011111000000111110000000001",
        "100000000000000000000000000001",
        "100000000000000000000000000001",
        "100000000111000000000111000001",
        "100000000010000000000010000001",
        "100000000010000000000010000001",
        "100111100010001110000010000001",
        "100000000010000010000010000001",
        "100000000000000010000000000001",
        "100000000000000010000000000001",
        "100000001111111110000111111001",
        "100000000000000000000000000101",
        "100000000000000000000000000101",
        "101111000000111111000000001101",
        "100001000000100001000000001001",
        "100001000000100001000000000001",
        "100001111111100001111111000001",
        "100000000000000000000000000001",
        "100000000000000000000000000001",
        "111111111111111111111111111111",
        NULL
    };
    int row_count = 0;
    char **map = NULL;

    for (; rows[row_count]; row_count++);
    map = malloc(sizeof(char *) * (row_count + 1));
    if (!map)
        return NULL;
    for (int i = 0; i < row_count; i++) {
        map[i] = malloc(sizeof(char) * (str_len(rows[i]) + 1));
        if (!map[i])
            return NULL;
        str_cpy(rows[i], map[i]);
    }
    map[row_count] = NULL;
    return map;
}

int main(void)
{
    char **map = create_map();
    raycast_t *raycast = raycast_create((char **)map, (ray_twod_t){15.5, 15.5});
    raycast->modification = &modif;
    setfml_t *setfml = setfml_ini(raycast);
    setfml_textureadd(setfml, "water", "./other.jpg");

    setfml_windowcreate(setfml);

    setfml_add(setfml, &(setfml_func_comp_t){NULL, &handle_keys}, "keys", LOOP_DATA);
    setfml_add(setfml, &(setfml_func_comp_t){NULL, &raycast_1}, "raycast", LOOP_DRAW);

    setfml_windowstart(setfml);
    setfml_destroy(setfml);
    raycast_destroy(raycast);
    for (int i = 0; i < 5; i++)
        free(map[i]);
    free(map);
    return 0;


    return 0;
}*/