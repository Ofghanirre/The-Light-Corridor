#include "scenery.h"
#include "utils.h"

Scenery GLOBAL_scenery;
int is_initialized = 0;

int scenery_init() {
    if (is_initialized) return -1;
    is_initialized = 1;
    GLOBAL_scenery.object_list = NULL;
    GLOBAL_scenery.last_object = NULL;
    GLOBAL_scenery.object_amount = 0;
    GLOBAL_scenery.bouncer = (Graphic_Object){
        {0. , 0., 0.}, 
        {0. , 0., 0.}, 
        make_circle((Point3D){0., 0., 0.}, 5., (ColorRGBA){1., 0., 0., 1.})
    };
    return CLEAR;
}

void scenery_free() {
    Node* iter = GLOBAL_scenery.object_list;
    while (iter != NULL) {
        Node * temp = iter;
        iter = iter->next;
        free(temp);
    }
}

void scenery_clear() {
    GLOBAL_scenery.object_amount = 0;
    scenery_free();
    is_initialized = 0;
    GLOBAL_scenery.last_object = NULL;
}


int scenery_append(Graphic_Object obj) {
    if (!is_initialized) return -1;
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return MEMORY_ERROR; // TODO HANDLE BETTER LATER ON

    GLOBAL_scenery.object_amount++;
    if (GLOBAL_scenery.last_object != NULL) GLOBAL_scenery.last_object->next = node;
    GLOBAL_scenery.last_object = node;

    return CLEAR;
}

int scenery_remove_first() {
    if (!is_initialized) return -1;
    if (GLOBAL_scenery.object_amount == 0) { return 1; }
    Node * temp = GLOBAL_scenery.object_list;
    GLOBAL_scenery.object_list = GLOBAL_scenery.object_list->next;
    GLOBAL_scenery.object_amount--;

    cfree(temp);
    return CLEAR;
}