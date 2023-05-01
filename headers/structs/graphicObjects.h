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
    struct Node* prev;
} Node;

typedef struct Graphic_Object_List {
    Node * head;
    Node * tail;
    int size;
} Graphic_Object_List, GO_List, GOL;

/**
 * @brief Represents the level of the game
 * Contains a name, a depth and all obstacles and bonuses
 * 
 * loaded with the parser from a .level file
 * 
 */
typedef struct Level {
    char * name;
    int depth;
    Graphic_Object_List obstacles;
    Graphic_Object_List bonus;
} Level;

/**
 * @brief Manage loaded levels for the game
 * The levels are loaded with the parser from ./resources/levels
 * 
 */
typedef struct LevelLoader {
    char ** levels;
    int size;
    int current_level;
    char * name;
} LevelLoader;

/* ------ Functions ------ */

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


void print_graphic_object(Graphic_Object object);

void print_GOL(Graphic_Object_List object);

/**
 * Creates a graphic_object corresponding to an obstacle. Its orientation is directly facing the camera
 * and its origin is in the center
*/
Graphic_Object new_obstacle(double width, double height, Point3D position, ColorRGBA color);

#endif