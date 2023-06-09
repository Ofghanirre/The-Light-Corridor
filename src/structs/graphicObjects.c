#include "structs/graphicObjects.h"
#include "structs/figures.h"

Graphic_Object_List new_graphic_object_list() {
    return (Graphic_Object_List){NULL, NULL, 0};
}

Node * alloc_new_node(Graphic_Object obj) {
    Node * node = (Node*) malloc(sizeof(Node));
    node->elem = obj;
    node->next = NULL;
    node->prev = NULL;

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
    if (list->tail != NULL) {
        list->tail->next = node;
        node->prev = list->tail;
    }
    list->tail = node;

    list->size++;
    return CLEAR;
}

int GOL_remove_first(Graphic_Object_List * list) {
    if (list->size == 0 || list->head == NULL) return -1;

    Node * temp = list->head;
    list->head = temp->next;
    free(temp);
    if (NULL != list->head) { list->head->prev = NULL; }
    list->size--;
    return CLEAR;
}

int GOL_remove(Graphic_Object_List * list, Node * object) {
    Node * temp = list->head;
    while (temp != NULL && temp != object) {
        temp = temp->next;
    }
    if (temp == NULL) return 1;
    if (temp->prev != NULL) { temp->prev->next = temp->next; }
    if (temp->next != NULL) { temp->next->prev = temp->prev; }
    if (temp == list->tail) { list->tail = temp->prev; }
    if (temp == list->head) { list->head = temp->next; }
    free(temp);
    list->size--;

    return CLEAR;
}

void print_graphic_object(Graphic_Object object) {
    print_log("Graphic_Object{");
    print_vec3D(object.position);
    print_log(",");
    print_vec3D(object.orientation);
    print_log(",");
    print_figure(object.figure);
    print_log(", effect : %d}", object.effect);
}

void print_GOL(Graphic_Object_List object) {
    print_log("List[%d]{\n",object.size);
    Node * iter = object.head;
    while (iter != NULL) {
        print_log("\t");
        print_graphic_object(iter->elem);
        print_log("\n");
        iter = iter->next;
    }
    print_log("}");
}

Graphic_Object new_obstacle(double width, double height, Point3D position, ColorRGBA color) {
    Graphic_Object result;
    result.figure.type = RECTANGLE;
    result.figure.color = color;
    result.figure.fig.rectangle.p1 = (Point3D){-width / 2., -height / 2., 0};
    result.figure.fig.rectangle.p2 = (Point3D){width / 2., height / 2., 0};
    result.position = position;
    result.orientation = (Vec3D){0., 0., 1.};
    result.effect = OBSTACLE;
    return result;
}

Graphic_Object new_bonus(double width, double height, Point3D position, ColorRGBA color, Effect effect) {
    Graphic_Object result;
    result.figure.type = RECTANGLE;
    result.figure.color = color;
    result.figure.fig.rectangle.p1 = (Point3D){-width / 2., -height / 2., 0};
    result.figure.fig.rectangle.p2 = (Point3D){width / 2., height / 2., 0};
    result.position = position;
    result.orientation = (Vec3D){0., 0., 1.};
    result.effect = effect;
    return result;
}