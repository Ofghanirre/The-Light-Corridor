#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

#include "controller.h"
#include "game.h"
#include "render.h"

/* Window properties */
const unsigned int WINDOW_WIDTH = 1000;
const unsigned int WINDOW_HEIGHT = 800;
const char WINDOW_TITLE[] = "TD04 Ex01";
float aspectRatio = 1.0;

/* Minimal time wanted between two images */
const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 50.;

/* Error handling function */
void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// if( aspectRatio > 1)
	// {
	// 	gluOrtho2D(
	// 	-GL_VIEW_SIZE / 2. * aspectRatio, 
    //     GL_VIEW_SIZE / 2. * aspectRatio,
	// 	-GL_VIEW_SIZE / 2., 
    //     GL_VIEW_SIZE / 2.);
	// }
	// else
	// {
	// 	gluOrtho2D(
	// 	-GL_VIEW_SIZE / 2., 
    //     GL_VIEW_SIZE / 2.,
	// 	-GL_VIEW_SIZE / 2. / aspectRatio, 
    //     GL_VIEW_SIZE / 2. / aspectRatio);
	// }

    gluPerspective(60.0, aspectRatio, 1, 200);
	glMatrixMode(GL_MODELVIEW);

}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				glfwSetWindowShouldClose(window, GLFW_TRUE); 
				break;
			case GLFW_KEY_L :
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				break;
			case GLFW_KEY_P :
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				break;
			default: fprintf(stdout,"Unhandled key : %d\n", key);
		}
	}
}

GLFWwindow* window_init() {
    GLFWwindow* window;
	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window) {
		return NULL;
	}


	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

    return window;
}

int run_game(GLFWwindow * window) {
    while (!glfwWindowShouldClose(window)) {
        double startTime = glfwGetTime();

        if (0 != game_tick()) {
             // HANDLE GAME TICK ERROR  
        }
        if (0 != render_tick()) {
             // HANDLE GAME TICK ERROR
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}
    }
    return 0;
}