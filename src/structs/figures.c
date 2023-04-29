#include "structs/figures.h"
#include <stdio.h>
#include "utils.h"


Figure make_rectangle(Point3D p1, Point3D p2, ColorRGBA color) {
    return (Figure){RECTANGLE, .fig.rectangle = (Figure_Rectangle){p1, p2}, color};
}

Figure make_circle(float radius, ColorRGBA color) {
    return (Figure){CIRCLE, .fig.circle = (Figure_Circle){radius}, color};
}

Figure make_sphere(float radius, ColorRGBA color) {
    return (Figure){SPHERE, .fig.sphere = (Figure_Sphere){radius}, color};
}

Figure make_label(const char* text, int font_size, ColorRGBA color) {
    return (Figure){LABEL, .fig.label = (Figure_Label){text, font_size}, color};
}

void print_figure_rectangle(Figure_Rectangle object) {
    print_log("Rectangle{");
    print_vec3D(object.p1);
    print_log(",");
    print_vec3D(object.p2);
    print_log("}");
}

void print_figure_circle(Figure_Circle object) {
    print_log("Circle{%f}",object.radius);
}

void print_figure_sphere(Figure_Sphere object) {
    print_log("Sphere{%f}",object.radius);
}

void print_figure_label(Figure_Label object) {
    print_log("Label{%s, %d}", object.text, object.font_size);
}

void print_figure(Figure object) {
    print_log("Figure{");
    switch(object.type) {
        case RECTANGLE : print_log("RECTANGLE,"); print_figure_rectangle(object.fig.rectangle); break;
        case CIRCLE : print_log("CIRCLE,"); print_figure_circle(object.fig.circle); break;
        case SPHERE : print_log("SPHERE,"); print_figure_sphere(object.fig.sphere); break;
        case LABEL : print_log("LABEL,"); print_figure_label(object.fig.label); break;
    }
    print_log(","); print_colorRGBA(object.color);
    print_log("}");
}