#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include <GLFW/glfw3.h>

/* Window properties */
extern const unsigned int WINDOW_WIDTH;
extern const unsigned int WINDOW_HEIGHT;
extern const char WINDOW_TITLE[];

/* Minimal time wanted between two images */
extern const double FRAMERATE_IN_SECONDS;

GLFWwindow* window_init();

int run_game(GLFWwindow * window);

#endif