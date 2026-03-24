#include "./../libs/classhandler/include/classhandler.h"

typedef struct player_s {
    int hp;
    int dmg;
    int move_speed;
} player_t;

typedef enum class_names_e {
    CLASS_PLAYERS
} class_names_t;

static int player_gethealth(entity_t *player)
{
    player_t *pl = NULL;

    if (!player || player->class->byte_size != sizeof(player_t))
        return -1;
    pl = (player_t *)player->data;
    return (pl->hp);
}

static int player_sethealth(entity_t *player, int hp)
{
    player_t *pl = NULL;

    if (!player || player->class->byte_size != sizeof(player_t))
        return -1;
    pl = (player_t *)player->data;
    pl->hp = hp;
    return 0;
}

int main(void)
{
    classhandler_t *classhandler = classhandler_init();
    class_t *class = NULL;
    entity_t *entity = NULL;

    if (!classhandler)
        return 84;
    class = classhandler_classcreate(classhandler, sizeof(player_t), "players");
    if (!class)
        return 84;
    entity = classhandler_entitycreate(classhandler, "players", "my_player");
    if (!entity)
        return 84;
    player_sethealth(entity, 95);
    printf("%d\n", player_gethealth(entity));
    classhandler_entitydestroy(classhandler, "players", "my_player");
    classhandler_classdestroy(classhandler, "players");
    classhandler_destroy(classhandler);
    return 0;
}
