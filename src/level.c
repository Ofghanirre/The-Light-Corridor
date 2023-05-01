#include "level.h"
#include "cparser.h"

int is_initialized = 0;

int level_init(Level *level, char * name, int depth) {
    if (is_initialized) return -1;
    is_initialized = 1;

    level->name = name;
    level->depth = depth;
    level->obstacles = new_graphic_object_list();
    level->bonus = new_graphic_object_list();

    return CLEAR;
}

void level_free(Level *level) {
    free(level->name);
    free_graphic_object_list(&(level->obstacles));
    free_graphic_object_list(&(level->bonus));
}

void level_clear(Level *level) {
    level_free(level);
    level->depth = 0;
    is_initialized = 0;
}

int level_append_obstacle(Level *level, Graphic_Object obj) {
    if (!is_initialized) return -1;
    return GOL_append_node(&(level->obstacles), obj);
}

int level_append_bonus(Level *level, Graphic_Object obj) {
    if (!is_initialized) return -1;
    return GOL_append_node(&(level->bonus), obj);
}

int level_remove_first_obstacle(Level *level) {
    if (!is_initialized) return -1;
    return GOL_remove_first(&(level->obstacles));
}

int level_remove_first_bonus(Level *level) {
    if (!is_initialized) return -1;
    return GOL_remove_first(&(level->bonus));
}

void print_level(Level * level) {
    print_log("Level{Name:%s,Depth:%d,\nObstacles:", level->name, level->depth);
    print_GOL(level->obstacles);
    print_log(",\nBonus:");
    print_GOL(level->bonus);
    print_log("\n}");
}

int loader_next_level(Level * result, LevelLoader * loader) {
    if (loader->current_level + 1 >= loader->size) { return 1; }
    loader->current_level++;
    return load_level(loader->levels[loader->current_level], result);
}