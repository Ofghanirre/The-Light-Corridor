#ifndef __GRAPHIC_OBJECTS_H__
#define __GRAPHIC_OBJECTS_H__

#include "vectors.h"
#include "figures.h"

typedef struct Graphic_Object {
    Point3D position;
    Vec3D orientation;
    Figure figure;
} Graphic_Object;

typedef struct Node {
    Graphic_Object obj;
    struct Node* next;
} Node;

typedef struct Scenery {
    Graphic_Object bouncer;
    Node* object_list;
    Node* last_object;
    int object_amount;
} Scenery;

#endif