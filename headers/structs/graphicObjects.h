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
 * Even if a Graphic_Object can be displayed, we want it to be wrapped up in an 
 * Graphic_Element struct so that we can display multiple Object as one element.
 * 
 * That can help creates multi-figure element
 */
typedef struct Graphic_Object {
    Point3D position;
    Vec3D orientation;
    Figure figure;
} Graphic_Object;

/**
 * @brief Represents an Element that can be displayed in the scene
 * Consists of a multiple of Graphic_Object, with differents positions and orientations
 * 
 * A Graphic_Element is really usefull to create template that can be easly placed / 
 * animated and removed.
 * 
 * The List is a dynamically allocated list, can be created with new_Graphic_Element,
 * and properly freed with free_Graphic_Element.
 * 
 * As some element can be pretty neet to create some functions have been implemented to
 * factorize the code for the creation of element such as the ball, walls, bonuses ect.
 * (new_ball, new_paddle, ect)
 */
typedef struct Graphic_Element {
    int object_amount;
    Graphic_Object* object_list;
} Graphic_Element;

/**
 * @brief Represents a Node for a linkedList of Graphic_Element
 * 
 */
typedef struct Node {
    Graphic_Element elem;
    struct Node* next;
} Node;

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
    Graphic_Element paddle;
    Graphic_Element ball;

    Node* obstacle_list;
    Node* last_obstacle;
    int obstacle_amount;

    Node* bonus_list;
    Node* last_bonus;
    int bonus_amount;
} Scenery;

/* ------ Functions ------ */

Graphic_Element new_Graphic_Element(Graphic_Object* objects, int size);
void free_Graphic_Element(Graphic_Element elem);
Graphic_Element new_ball();
Graphic_Element new_paddle();
#endif