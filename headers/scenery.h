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
 * @brief Append a Graphic_Element to the end of the scenery stack
 * Increases the scenery.object_amount by 1
 * 
 * @param obj 
 * @return - int -1 if the scenery hasn't been initialized, thus not creating the object
 * - MEMORY_ERROR if the object could not been allocated
 * - int 0 if clear
 */
int scenery_append_obstacle(Graphic_Element elem);
int scenery_append_bonus(Graphic_Element elem);

/**
 * @brief Removes a Graphic_Element at the start of the scenery stack
 * Increases the scenery.object_amount by 1
 * 
 * @param obj 
 * @return - int -1 if the object hasn't been initialized, thus not creating the object
 * - int 1 if the stack is empty
 * - int 0 if clear
 */
int scenery_remove_first_obstacle();
int scenery_remove_first_bonus();


#endif