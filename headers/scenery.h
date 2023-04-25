#ifndef __SCENERY_H__
#define __SCENERY_H__

#include "structs/graphicObjects.h"

extern Scenery GLOBAL_scenery;
#define scenery GLOBAL_scenery

/**
 * @brief Initialize the scenery global
 * No scenery functions shall work properly if the scenery hasn't been properly initialized
 * 
 * @return int -1 if already initialized
 * @return int 0 if clear
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
 * @brief Append a Graphic_Object to the end of the scenery stack
 * Increases the scenery.object_amount by 1
 * 
 * @param obj 
 * @return int -1 if the object hasn't been initialized, thus not creating the object
 * @return MEMORY_ERROR if the object could not been allocated
 * @return int 0 if clear
 */
int scenery_append(Graphic_Object obj);

/**
 * @brief Append a Graphic_Object to the end of the scenery stack
 * Increases the scenery.object_amount by 1
 * 
 * @param obj 
 * @return int -1 if the object hasn't been initialized, thus not creating the object
 * @return int 1 if the stack is empty
 * @return int 0 if clear
 */
int scenery_remove_first();


#endif