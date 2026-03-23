#include "./../libs/raycaster/include/raycaster.h"
#include "./../libs/setfml/setfml.h"

size_t raycast_1(setfml_t *setfml, void *userdata)
{
    raycast_t *ray = (raycast_t *)setfml->userdata;
    printf("%zu\n", raycast_raycast(ray));
    return SETFML_SUCC;
}

size_t raycast_2(setfml_t *setfml, void *userdata)
{
    raycast_t *ray = (raycast_t *)setfml->userdata;
    raycast_render(ray, setfml->window);
    return SETFML_SUCC;
}

int main(void)
{
    char **map = malloc(sizeof(char *) * 6);
    map[5] = NULL;
    for (int i = 0; i < 5; i++)
        map[i] = malloc(sizeof(char) * 6);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            map[i][j] = '1';
    }
    for (int i = 1; i < 4; i++) {
        for (int j = 1; j < 4; j++)
            map[i][j] = '0';
    }
    for (int i = 0; i < 5; i++)
        map[i][5] = 0;
    map[2][3] = '1';
    map[3][2] = '1';
    map[3][3] = '1';

    raycast_t *raycast = raycast_create((char **)map, (ray_twod_t){1.5, 1.5});

    setfml_t *setfml = setfml_ini(raycast);

    setfml_windowcreate(setfml);
    raycast_raycast(raycast);
    raycast_render(raycast, setfml->window);
    setfml_add(setfml, &(setfml_func_comp_t){&raycast_1, NULL}, "raycast", LOOP_DATA);

    setfml_windowstart(setfml);
    setfml_destroy(setfml);
    raycast_destroy(raycast);
    for (int i = 0; i < 5; i++)
        free(map[i]);
    free(map);
    return 0;


    return 0;
}