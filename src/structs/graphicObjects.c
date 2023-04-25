#include "structs/graphicObjects.h"

Graphic_Element new_Graphic_Element(Graphic_Object* objects, int size) {
    return (Graphic_Element){size, objects};
}

void free_Graphic_Element(Graphic_Element elem) {
    cfree(elem.object_list);
}

Graphic_Element new_ball() {
    Graphic_Object * objects = (Graphic_Object*) malloc(sizeof(Graphic_Object) * 1);
    if (objects == NULL) {
        __FLAG_MEMORY_ERROR__ = 1;
    }
    objects[0] = (Graphic_Object){{0., 0., 0.}, {0., 0., 0.}, make_sphere(1., (ColorRGBA){1., 0., 0., 1.}) };
    return new_Graphic_Element(objects, 1);
}

Graphic_Element new_paddle() {
    Graphic_Object * objects = (Graphic_Object*) malloc(sizeof(Graphic_Object) * 1);
    if (objects == NULL) {
        __FLAG_MEMORY_ERROR__ = 1;
    }
    objects[0] = (Graphic_Object){{0., 0., 0.}, {0., 0., 0.}, make_rectangle((Point3D){-0.5, -0.5, 0.}, (Point3D){0.5, 0.5, 0.}, (ColorRGBA){0., 0., 1., 1.}) };
    return new_Graphic_Element(objects, 1);
}
