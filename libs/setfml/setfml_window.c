/*
** EPITECH PROJECT, 2025
** setfml
** File description:
** Tired of initializing csfml? Up your workflow with this simple wrapper.
*/

#include "./setfml.h"

size_t setfml_windowcreate(setfml_t *setfml)
{
    params_t params = setfml->params;
    sfVideoMode mode = {
        setfml->params.window.max_scr_res[0],
        setfml->params.window.max_scr_res[1],
        8};
    sfRenderWindow *window = sfRenderWindow_create(
        mode,
        params.window.title,
        params.window.style,
        params.window.settings);

    if (!window)
        return (size_t)SETFML_FAIL;
    setfml->window = window;
    sfRenderWindow_setFramerateLimit(window, (unsigned int)params.window.fps);
    return (size_t)SETFML_SUCC;
}

size_t setfml_windowstart(setfml_t *setfml)
{
    sprite_t *sprite = NULL;
    sfVector2u windowsize = sfRenderWindow_getSize(setfml->window);

    if (!setfml || !setfml->window)
        return (size_t)SETFML_FAIL;
    for (node_t *node = setfml->sprites->head; node; node = node->next) {
        sprite = (sprite_t *)node->data;
        sprite->original_win_x = windowsize.x;
        sprite->original_win_y = windowsize.y;
    }
    sfRenderWindow_display(setfml->window);
    while (sfRenderWindow_isOpen(setfml->window))
        setfml_iteration(setfml);
    return (size_t)SETFML_SUCC;
}

size_t setfml_windowclose(setfml_t *setfml)
{
    if (!setfml || !setfml->window)
        return (size_t)SETFML_FAIL;
    sfRenderWindow_close(setfml->window);
    return (size_t)SETFML_SUCC;
}

size_t setfml_windowdestroy(setfml_t *setfml)
{
    if (!setfml || !setfml->window)
        return (size_t)SETFML_FAIL;
    sfRenderWindow_destroy(setfml->window);
    setfml->window = NULL;
    return (size_t)SETFML_SUCC;
}
