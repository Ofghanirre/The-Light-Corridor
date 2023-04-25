#include "structs/colors.h"

ColorRGBA rgb_to_rgba(ColorRGB color) {
    return (ColorRGBA){color.r, color.g, color.b, 1.0};
}

ColorRGB rgba_to_rgb(ColorRGBA color) {
    return (ColorRGB){color.r, color.g, color.b};
}