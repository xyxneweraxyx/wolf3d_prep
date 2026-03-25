/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** Raycast callbacks to setfml.
*/

#include "./../../include/wolf3d.h"

static void load_setfml(setfml_t *setfml)
{
    setfml_textureadd(setfml, "wall", SFML_TXT_WALL);
}

int ini_csfml_env(wolf_t *wolf)
{
    setfml_t *setfml = NULL;
    buttonfml_t *buttonfml = NULL;

    if (!wolf)
        return WOLF_FAIL;
    setfml = setfml_ini((void *)wolf);
    if (!setfml)
        return WOLF_FAIL;
    wolf->setfml = setfml;
    buttonfml = buttonfml_ini(setfml);
    if (!buttonfml)
        return WOLF_FAIL;
    wolf->buttonfml = buttonfml;
    load_setfml(setfml);
    return WOLF_SUCC;
}