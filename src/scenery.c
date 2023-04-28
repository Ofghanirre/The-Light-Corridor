#include "scenery.h"


Scenery GLOBAL_scenery;
int is_initialized = 0;

int scenery_init(Scenery *scenery) {
    if (is_initialized) return -1;
    is_initialized = 1;

    scenery->obstacles = new_graphic_object_list();
    scenery->bonus = new_graphic_object_list();

    return CLEAR;
}

void scenery_free(Scenery *scenery) {
    free_graphic_object_list(&(scenery->obstacles));
    free_graphic_object_list(&(scenery->bonus));
}

void scenery_clear(Scenery *scenery) {
    scenery_free(scenery);
    is_initialized = 0;
}

int scenery_append_obstacle(Scenery *scenery, Graphic_Object obj) {
    if (!is_initialized) return -1;
    return GOL_append_node(&(scenery->obstacles), obj);
}

int scenery_append_bonus(Scenery *scenery, Graphic_Object obj) {
    if (!is_initialized) return -1;
    return GOL_append_node(&(scenery->bonus), obj);
}

int scenery_remove_first_obstacle(Scenery *scenery) {
    if (!is_initialized) return -1;
    return GOL_remove_first(&(scenery->obstacles));
}

int scenery_remove_first_bonus(Scenery *scenery) {
    if (!is_initialized) return -1;
    return GOL_remove_first(&(scenery->bonus));
}