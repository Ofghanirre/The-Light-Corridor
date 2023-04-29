#include "structs/figures.h"
#include <stdio.h>

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
    printf("Rectangle{");
    print_vec3D(object.p1);
    printf(",");
    print_vec3D(object.p2);
    printf("}");
}

void print_figure_circle(Figure_Circle object) {
    printf("Circle{%f}",object.radius);
}

void print_figure_sphere(Figure_Sphere object) {
    printf("Sphere{%f}",object.radius);
}

void print_figure_label(Figure_Label object) {
    printf("Label{%s, %d}", object.text, object.font_size);
}

void print_figure(Figure object) {
    printf("Figure{");
    switch(object.type) {
        case RECTANGLE : printf("RECTANGLE,"); print_figure_rectangle(object.fig.rectangle); break;
        case CIRCLE : printf("CIRCLE,"); print_figure_circle(object.fig.circle); break;
        case SPHERE : printf("SPHERE,"); print_figure_sphere(object.fig.sphere); break;
        case LABEL : printf("LABEL,"); print_figure_label(object.fig.label); break;
    }
    printf(","); print_colorRGBA(object.color);
    printf("}");
}