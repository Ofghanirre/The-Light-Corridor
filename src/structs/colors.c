#include "structs/colors.h"
#include <stdio.h>

ColorRGBA rgb_to_rgba(ColorRGB color) {
    return (ColorRGBA){color.r, color.g, color.b, 1.0};
}

ColorRGB rgba_to_rgb(ColorRGBA color) {
    return (ColorRGB){color.r, color.g, color.b};
}

void print_colorRGBA(ColorRGBA color) {
    printf("ColorRGBA{%f, %f, %f, %f}", color.r, color.g, color.b, color.a);
}

void print_colorRGB(ColorRGBA color) {
    printf("ColorRGB{%f, %f, %f}", color.r, color.g, color.b);
}