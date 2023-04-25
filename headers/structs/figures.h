#ifndef __FIGURES_H__
#define __FIGURES_H__

#include "vectors.h"
#include "colors.h"

/* ------ Structs ------ */
typedef enum FigureType {
    RECTANGLE,
    CIRCLE,
    SPHERE,
    LABEL
} FigureType;

typedef struct Figure_Rectangle {
    Point3D p1, p2;
} Figure_Rectangle;

typedef struct Figure_Circle {
    Point3D center;
    float radius;
} Figure_Circle, Figure_Sphere;

typedef struct Figure_Label {
    const char* text;
    int font_size;
} Figure_Label;

typedef struct Figure {
    FigureType type;
    union {
        Figure_Rectangle    rectangle;
        Figure_Circle       circle;
        Figure_Sphere       sphere;
        Figure_Label        label;
    } fig;
    ColorRGBA color;
} Figure;

/* ------ Functions ------*/

Figure make_rectangle(Point3D p1, Point3D p2, ColorRGBA color);
Figure make_circle(Point3D center, float radius, ColorRGBA color);
Figure make_sphere(Point3D center, float radius, ColorRGBA color);
Figure make_label(const char* text, int font_size, ColorRGBA color);

#endif