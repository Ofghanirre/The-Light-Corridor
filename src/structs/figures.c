#include "structs/figures.h"

Figure make_rectangle(Point3D p1, Point3D p2, ColorRGBA color) {
    return (Figure){RECTANGLE, .fig.rectangle = (Figure_Rectangle){p1, p2}, color};
}

Figure make_circle(Point3D center, float radius, ColorRGBA color) {
    return (Figure){CIRCLE, .fig.circle = (Figure_Circle){center, radius}, color};
}

Figure make_sphere(Point3D center, float radius, ColorRGBA color) {
    return (Figure){SPHERE, .fig.sphere = (Figure_Sphere){center, radius}, color};
}

Figure make_label(const char* text, int font_size, ColorRGBA color) {
    return (Figure){LABEL, .fig.label = (Figure_Label){text, font_size}, color};
}