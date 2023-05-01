#ifndef __SCENERY_H__
#define __SCENERY_H__

#include "structs/graphicObjects.h"
#include "utils.h"

/**
 * @brief Initialize the level
 * No level functions shall work properly if the level hasn't been properly initialized
 * 
 * @return - int -1 if already initialized
 * - int 0 if clear
 */
int level_init(Level *level, char * name, int depth);

/**
 * @brief Clear the level
 * Need a new initialization for the level to work again
 * 
 */
void level_clear(Level *level);

/**
 * @brief Free the level
 * 
 */
void level_free(Level *level);

/**
 * @brief Append a Graphic_Object to the obstacles of the level
 * 
 * @param obj 
 * @return - int -1 if the level hasn't been initialized, thus not creating the object
 * - MEMORY_ERROR if the object could not been allocated (the flag __FLAG_MEMORY_ERROR__ will be raised)
 * - int 0 if clear
 */
int level_append_obstacle(Level *level, Graphic_Object obj);

/**
 * @brief Append a Graphic_Object to the bonus of the level
 * 
 * @param obj 
 * @return - int -1 if the level hasn't been initialized, thus not creating the object
 * - MEMORY_ERROR if the object could not been allocated (the flag __FLAG_MEMORY_ERROR__ will be raised)
 * - int 0 if clear
 */
int level_append_bonus(Level *level, Graphic_Object obj);

/**
 * @brief Removes a Graphic_Object of the level's obstacles
 * 
 * @param obj 
 * @return - int -1 if the object hasn't been initialized, thus not creating the object
 * - int 1 if the stack is empty
 * - int 0 if clear
 */
int level_remove_first_obstacle(Level *level);

/**
 * @brief Removes a Graphic_Object of the level's obstacles
 * 
 * @param obj 
 * @return - int -1 if the object hasn't been initialized, thus not creating the object
 * - int 1 if the stack is empty
 * - int 0 if clear
 */
int level_remove_first_bonus(Level *level);

void print_level(Level * level);

#define NO_NEXT_LEVEL -42

/**
 * @brief Invoke and load the next level on the loader into result, if no next lever,
 * the int NO_NEXT_LEVEL is returned
 * 
 * @param result 
 * @param loader 
 * @return int 
 */
int loader_next_level(Level * result, LevelLoader * loader);

/**
 * @brief Free the given loader
 * 
 * @param loader 
 */
void loader_free(LevelLoader* loader);
#endif