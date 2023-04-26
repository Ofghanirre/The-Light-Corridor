#include "structs/graphicObjects.h"

Graphic_Object new_ball() {
    return  (Graphic_Object){{0., 0., 0.}, {0., 0., 0.}, make_sphere(1., (ColorRGBA){1., 0., 0., 1.}) };
}

Graphic_Object new_paddle() {
    return (Graphic_Object){{0., 0., 0.}, {0., 0., 0.}, make_rectangle((Point3D){-0.5, -0.5, 0.}, (Point3D){0.5, 0.5, 0.}, (ColorRGBA){0., 0., 1., 1.}) };
}
