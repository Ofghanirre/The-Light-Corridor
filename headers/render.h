#ifndef __RENDER_H
#define __RENDER_H

/**
 * Indicates how much behind the camera is compared to the paddle
*/
#define CAMERA_OFFSET 30

#define NB_TEXTURES 5
/**
 * Structure containing the information for a texture
*/
typedef struct textures_s {
    unsigned int gl_texture[NB_TEXTURES];    /** Handle for the texture in openGL */
    unsigned char* data[NB_TEXTURES];        /** Data of the texture in RAM */
} textures_t;

void render_init();

void render_free();

int render_tick();

#endif