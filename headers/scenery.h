#ifndef __SCENERY_H__
#define __SCENERY_H__

#include "structs/graphicObjects.h"
#include "utils.h"

extern Scenery GLOBAL_scenery;
#define scenery GLOBAL_scenery

/**
 * @brief Initialize the scenery global
 * No scenery functions shall work properly if the scenery hasn't been properly initialized
 * 
 * @return - int -1 if already initialized
 * - int 0 if clear
 */
int scenery_init();

/**
 * @brief Clear the scenery global
 * Need a new initialization for the scenery to work again
 * 
 */
void scenery_clear();

/**
 * @brief Free the scenery global
 * 
 */
void scenery_free();

/**
 * @brief Append a Graphic_Object to the obstacles of the scenery
 * 
 * @param obj 
 * @return - int -1 if the scenery hasn't been initialized, thus not creating the object
 * - MEMORY_ERROR if the object could not been allocated (the flag __FLAG_MEMORY_ERROR__ will be raised)
 * - int 0 if clear
 */
int scenery_append_obstacle(Graphic_Object obj);

/**
 * @brief Append a Graphic_Object to the bonus of the scenery
 * 
 * @param obj 
 * @return - int -1 if the scenery hasn't been initialized, thus not creating the object
 * - MEMORY_ERROR if the object could not been allocated (the flag __FLAG_MEMORY_ERROR__ will be raised)
 * - int 0 if clear
 */
int scenery_append_bonus(Graphic_Object obj);

/**
 * @brief Removes a Graphic_Object of the scenery's obstacles
 * 
 * @param obj 
 * @return - int -1 if the object hasn't been initialized, thus not creating the object
 * - int 1 if the stack is empty
 * - int 0 if clear
 */
int scenery_remove_first_obstacle();

/**
 * @brief Removes a Graphic_Object of the scenery's obstacles
 * 
 * @param obj 
 * @return - int -1 if the object hasn't been initialized, thus not creating the object
 * - int 1 if the stack is empty
 * - int 0 if clear
 */
int scenery_remove_first_bonus();

void print_scenery();

#endif