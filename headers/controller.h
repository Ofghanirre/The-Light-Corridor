#ifndef __CONTROLLER_H
#define __CONTROLLER_H

/* Window properties */
extern static const unsigned int WINDOW_WIDTH;
extern static const unsigned int WINDOW_HEIGHT;
extern static const char WINDOW_TITLE[];

/* Minimal time wanted between two images */
extern static const double FRAMERATE_IN_SECONDS;

GLFWwindow* window_init();

int run_game(GLFWwindow * window);

#endif