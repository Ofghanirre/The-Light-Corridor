#include "structs/graphicObjects.h"

Graphic_Object_List new_graphic_object_list() {
    return (Graphic_Object_List){NULL, NULL, 0};
}

Node * alloc_new_node(Graphic_Object obj) {
    Node * node = (Node*) malloc(sizeof(Node));
    node->elem = obj;
    node->next = NULL;

    if (node == NULL) {
        fprintf(stderr, "Allocation Error on alloc_new_node\n");
        __FLAG_MEMORY_ERROR__ = 1;
    }

    return node;
}

void free_graphic_object_list(Graphic_Object_List * obj) {
    Node * iter = obj->head;
    while (iter != NULL) {
        Node * temp = iter;
        iter = iter->next;

        free(temp);
    }
    obj->head = NULL;
    obj->tail = NULL;
    obj->size = 0;
}

int GOL_append_node(Graphic_Object_List * list, Graphic_Object obj) {
    Node * node = alloc_new_node(obj);
    if (__FLAG_MEMORY_ERROR__) return MEMORY_ERROR;
    if (list->head == NULL) list->head = node;
    if (list->tail != NULL) list->tail->next = node;
    list->tail = node;

    list->size++;
    return CLEAR;
}

int GOL_remove_first(Graphic_Object_List * list) {
    if (list->size == 0 || list->head == NULL) return -1;

    Node * temp = list->head;
    list->head = temp->next;
    free(temp);
    list->size--;
    return CLEAR;
}