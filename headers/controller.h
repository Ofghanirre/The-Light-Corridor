#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include <GLFW/glfw3.h>
#include "structs/vectors.h"

/* Window properties */
extern const unsigned int WINDOW_WIDTH;
extern const unsigned int WINDOW_HEIGHT;
extern const char WINDOW_TITLE[];

/* Minimal time wanted between two images */
extern const double FRAMERATE_IN_SECONDS;

#define CORRIDOR_WIDTH 50
#define CORRIDOR_HEIGHT 30

#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 10
#define PADDLE_Z 0

/**
 * Represents the paddle
 * x, y coordinates are at the center of the rectangular shaped paddle
*/
typedef struct paddle_s {
    Vec2D position;
} paddle_t;

#define BALL_RADIUS 2.5

typedef struct ball_s {
    Vec3D position;
    Vec3D velocity;

    Vec2D glued_offset;
    int glued;
} ball_t;

typedef struct game_state_s {
    double camera_pos;
    paddle_t paddle;
    ball_t ball;
    int glue_enabled;
} game_state_t;

extern game_state_t game_state;

GLFWwindow* window_init();

int run_game(GLFWwindow * window);

#endif