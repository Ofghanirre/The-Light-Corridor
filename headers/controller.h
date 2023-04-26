#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include <GLFW/glfw3.h>

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
    double x;
    double y;
} paddle_t;

typedef struct game_state_s {
    paddle_t paddle;
} game_state_t;

extern game_state_t game_state;

GLFWwindow* window_init();

int run_game(GLFWwindow * window);

#endif