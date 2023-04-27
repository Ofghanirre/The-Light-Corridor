#ifndef __GRAPHIC_OBJECTS_H__
#define __GRAPHIC_OBJECTS_H__

#include "vectors.h"
#include "figures.h"
#include "utils.h"

/* ------ Structs ------ */

/**
 * @brief Represents an Object that can be displayed in the scene
 * The objects consists of a geometrical figure, a 3d position and orientation
 * 
 * As some element can be pretty neet to create some functions have been implemented to
 * factorize the code for the creation of element such as the ball, paddle
 */
typedef struct Graphic_Object {
    Point3D position;
    Vec3D orientation; 
    Figure figure;
} Graphic_Object;


/**
 * @brief Represents a Node for a linkedList of Graphic_Element
 * 
 */
typedef struct Node {
    Graphic_Object elem;
    struct Node* next;
} Node;

typedef struct Graphic_Object_List {
    Node * head;
    Node * tail;
    int size;
} Graphic_Object_List, GO_List, GOL;

/**
 * @brief Represents the scenery of the game
 * Contains all non-const objects that will be displayed like 
 * - ball
 * - paddle
 * - obstacles
 * - bonuses
 * 
 */
typedef struct Scenery {
    Graphic_Object paddle;
    Graphic_Object ball;
    Graphic_Object_List obstacles;
    Graphic_Object_List bonus;
} Scenery;

/* ------ Functions ------ */

Graphic_Object new_ball();
Graphic_Object new_paddle();

/**
 * @brief Returns a new, empty GOL
 * 
 * @return Graphic_Object_List 
 */
Graphic_Object_List new_graphic_object_list();

/**
 * @brief Free and clears a given GOL
 * 
 * @param obj 
 */
void free_graphic_object_list(Graphic_Object_List * obj);

/**
 * @brief Create, allocates and append a new Graphic_Object into a GOL
 * within a Node.
 * The node is added at the end of the list.
 * 
 * As there is an allocation the flag __FLAG_MEMORY_ERROR__ can be raised and need
 * to be looked over while using the function.
 * 
 * @param list 
 * @param obj 
 * @return int 
 */
int GOL_append_node(Graphic_Object_List * list, Graphic_Object obj);

/**
 * @brief Remove and free the head of the list
 * 
 * @param list 
 * @return int 
 */
int GOL_remove_first(Graphic_Object_List * list);
#endif