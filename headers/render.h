#ifndef __RENDER_H
#define __RENDER_H

/**
 * Indicates how much behind the camera is compared to the paddle
*/
#define CAMERA_OFFSET 30

void render_init();

void render_free();

int render_tick();

#endif