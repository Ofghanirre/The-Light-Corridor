#ifndef __FIGURES_H__
#define __FIGURES_H__

#include "vectors.h"
#include "colors.h"

/* ------ Structs ------ */

/**
 * @brief List the possibles figures type
 * 
 */
typedef enum FigureType {
    RECTANGLE,
    CIRCLE,
    SPHERE,
    LABEL
} FigureType;

/**
 * @brief Represents a rectangle focused on position (0,0,0)
 * Its height / width is then calculated with the "top-left" point and the "down-right" point
 * 
 */
typedef struct Figure_Rectangle {
    Point3D p1, p2;
} Figure_Rectangle;

/**
 * @brief Represents a circle / sphere focused on position (0,0,0)
 */
typedef struct Figure_Circle {
    float radius;
} Figure_Circle, Figure_Sphere;

/**
 * @brief Represents a label centered on position (0,0,0)
 */
typedef struct Figure_Label {
    const char* text;
    float font_size;
} Figure_Label;

/**
 * @brief Represents a figure that is to be drawn on the screen, keep in mind that this
 * struct merely represents the data of the figure. It does not hold the position /
 * direction information and thus can not be displayed like so.
 * 
 * To be displayed it needs to be used in a Graphic_Object
 * 
 */
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
Figure make_circle(float radius, ColorRGBA color);
Figure make_sphere(float radius, ColorRGBA color);
Figure make_label(const char* text, float font_size, ColorRGBA color);

void print_figure(Figure object);
#endif