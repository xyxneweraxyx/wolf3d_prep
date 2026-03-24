/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** Main entry point of wolf3d.
*/

#include "./../include/wolf3d.h"

// Fonction temporaire pour faire une map vu que je connais pas les consignes
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

// Même chose
static void free_map(char **map)
{
    for (int i = 0; map[i]; i++)
        free(map[i]);
    free(map);
}

static int destroy_return_int(int RET_CODE, wolf_t *wolf)
{
    if (!wolf)
        return RET_CODE;
    if (wolf->buttonfml)
        buttonfml_destroy(wolf->buttonfml);
    if (wolf->setfml)
        setfml_destroy(wolf->setfml);
    if (wolf->map)
        free_map(wolf->map);
    if (wolf->alloc)
        c_delete(wolf->alloc, true);
    return RET_CODE;
}

static void *destroy_return_null(wolf_t *wolf)
{
    if (!wolf)
        return NULL;
    if (wolf->buttonfml)
        buttonfml_destroy(wolf->buttonfml);
    if (wolf->setfml)
        setfml_destroy(wolf->setfml);
    if (wolf->map)
        free_map(wolf->map);
    if (wolf->alloc)
        c_delete(wolf->alloc, true);
    return NULL;
}

static int ini_csfml_env(wolf_t *wolf)
{
    setfml_t *setfml = NULL;
    buttonfml_t *buttonfml = NULL;

    if (!wolf)
        return destroy_return_int(WOLF_FAIL, wolf);
    setfml = setfml_ini((void *)wolf);
    if (!setfml)
        return destroy_return_int(WOLF_FAIL, wolf);
    wolf->setfml = setfml;
    buttonfml = buttonfml_ini(setfml);
    if (!buttonfml)
        return destroy_return_int(WOLF_FAIL, wolf);
    wolf->buttonfml = buttonfml;
    return WOLF_SUCC;
}

static wolf_t *ini_main(c_alloc_t *alloc)
{
    wolf_t *wolf = NULL;

    if (!alloc)
        return NULL;
    wolf = c_alloc(sizeof(wolf_t), 1, alloc);
    if (!wolf) {
        c_delete(alloc, false);
        return destroy_return_null(wolf);
    }
    wolf->alloc = alloc;
    wolf->map = create_map();
    if (!wolf->map) {
        c_delete(alloc, true);
        return destroy_return_null(wolf);
    }
    return wolf;
}

int main(void)
{
    c_alloc_t *alloc = c_ini((uint16_t)100);
    wolf_t *wolf = ini_main(alloc);

    if (!wolf)
        return WOLF_FAIL;
    if (ini_csfml_env(wolf) == WOLF_FAIL)
        return WOLF_FAIL;
    return destroy_return_int(WOLF_SUCC, wolf);
}