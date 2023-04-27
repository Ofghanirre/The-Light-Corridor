#include "scenery.h"


Scenery GLOBAL_scenery;
int is_initialized = 0;

int scenery_init() {
    if (is_initialized) return -1;
    is_initialized = 1;

    GLOBAL_scenery.obstacles = new_graphic_object_list();
    GLOBAL_scenery.bonus = new_graphic_object_list();

    GLOBAL_scenery.paddle = new_paddle();
    GLOBAL_scenery.ball = new_ball();

    return CLEAR;
}

void scenery_free() {
    free_graphic_object_list(&(GLOBAL_scenery.obstacles));
    free_graphic_object_list(&(GLOBAL_scenery.bonus));
}

void scenery_clear() {
    scenery_free();
    is_initialized = 0;
}

int scenery_append_obstacle(Graphic_Object obj) {
    if (!is_initialized) return -1;
    return GOL_append_node(&(GLOBAL_scenery.obstacles), obj);
}

int scenery_append_bonus(Graphic_Object obj) {
    if (!is_initialized) return -1;
    return GOL_append_node(&(GLOBAL_scenery.bonus), obj);
}

int scenery_remove_first_obstacle() {
    if (!is_initialized) return -1;
    return GOL_remove_first(&(GLOBAL_scenery.obstacles));
}

int scenery_remove_first_bonus() {
    if (!is_initialized) return -1;
    return GOL_remove_first(&(GLOBAL_scenery.bonus));
}