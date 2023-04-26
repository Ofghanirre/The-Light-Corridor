#include "scenery.h"


Scenery GLOBAL_scenery;
int is_initialized = 0;

int scenery_init() {
    if (is_initialized) return -1;
    is_initialized = 1;

    GLOBAL_scenery.obstacle_list = NULL;
    GLOBAL_scenery.last_obstacle = NULL;
    GLOBAL_scenery.obstacle_amount = 0;

    GLOBAL_scenery.bonus_list = NULL;
    GLOBAL_scenery.last_bonus = NULL;
    GLOBAL_scenery.bonus_amount = 0;

    GLOBAL_scenery.paddle = new_paddle();
    GLOBAL_scenery.ball = new_ball();

    return CLEAR;
}
void free_linked_list(Node** list) {
    Node* iter = *list;
    while (iter != NULL) {
        Node * temp = iter;
        iter = iter->next;
        free(temp);
    }
    *list = NULL;
}

void scenery_free() {
    free_linked_list(&(GLOBAL_scenery.obstacle_list));
    free_linked_list(&(GLOBAL_scenery.bonus_list));
}

void scenery_clear() {
    scenery_free();
    GLOBAL_scenery.obstacle_amount = 0;
    GLOBAL_scenery.bonus_amount = 0;
    GLOBAL_scenery.last_obstacle = NULL;
    GLOBAL_scenery.last_obstacle = NULL;
    is_initialized = 0;
}


int scenery_append(Graphic_Object elem, Node ** list, Node** last_elem, int * list_size) {
    if (!is_initialized) return -1;
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return MEMORY_ERROR; // TODO HANDLE BETTER LATER ON
    node->elem = elem;
    node->next = NULL;
    (*list_size)++;
    if ((*last_elem) != NULL) (*last_elem)->next = node;
    if ((*list) == NULL) { (*list) = node; }
    (*last_elem) = node;

    return CLEAR;
}

int scenery_append_obstacle(Graphic_Object obj) {
    return scenery_append(obj, &(GLOBAL_scenery.obstacle_list), &(GLOBAL_scenery.last_obstacle), &(GLOBAL_scenery.obstacle_amount));
}

int scenery_append_bonus(Graphic_Object obj) {
    return scenery_append(obj, &(GLOBAL_scenery.bonus_list),  &(GLOBAL_scenery.last_bonus), &(GLOBAL_scenery.bonus_amount));
}

int scenery_remove_first(Node ** list, Node** last_elem, int * list_size) {
    if (!is_initialized) return -1;
    if ((*list_size) == 0) { return 1; }
    Node * temp = (*list);
    *list = (*list)->next;
    (*list_size)--;
    if ((*list_size) == 0) {
        *last_elem = NULL;
    }
    free(temp);
    return CLEAR;
}

int scenery_remove_first_obstacle() {
    return scenery_remove_first(&(GLOBAL_scenery.obstacle_list), &(GLOBAL_scenery.last_obstacle), &(GLOBAL_scenery.obstacle_amount));
}

int scenery_remove_first_bonus() {
    return scenery_remove_first(&(GLOBAL_scenery.bonus_list), &(GLOBAL_scenery.last_bonus), &(GLOBAL_scenery.bonus_amount));
}