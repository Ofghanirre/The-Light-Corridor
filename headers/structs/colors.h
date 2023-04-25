#ifndef __COLORS_H__
#define __COLORS_H__

/* ------ Structs ------*/

typedef struct ColorRGB {
    float r, g, b;
} ColorRGB;

typedef struct ColorRGBA {
    float r, g, b, a;
} ColorRGBA;


/* ------ Functions ------*/


ColorRGBA rgb_to_rgba(ColorRGB color);
ColorRGB rgba_to_rgb(ColorRGBA color);

#endif