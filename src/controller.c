#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

#include "controller.h"
#include "game.h"
#include "render.h"

/* Window properties */
const unsigned int WINDOW_WIDTH = 1200;
const unsigned int WINDOW_HEIGHT = 720;
const char WINDOW_TITLE[] = "The Light Corridor";
float aspectRatio = 1.0;

/* Minimal time wanted between two images */
const double FRAMERATE_IN_SECONDS = 1. / 60.;

game_state_t game_state;

/* Error handling function */
static void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

static void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;
	glViewport(0, 0, width, height);
}

static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
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
            case GLFW_KEY_LEFT:
                game_state.level_selected -= 1;
                break;
            case GLFW_KEY_RIGHT:
                game_state.level_selected += 1;
                break;
            case GLFW_KEY_ENTER:
                game_start();
                break;
			default: fprintf(stdout, "Unhandled key : %d\n", key);
		}
	}
}

static void cursor_position_callback(GLFWwindow* window, double x, double y)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    game_state.paddle.position.x = (x / width - 0.5) * CORRIDOR_WIDTH;
    game_state.paddle.position.y = (0.5 - y / height) * CORRIDOR_HEIGHT;
    clamp_paddle_position();
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        game_state.ball.glued = 0;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        game_state.moving_forward = 1;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        game_state.moving_forward = 0;
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
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

    /* Hides mouse cursor */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    return window;
}

int run_game(GLFWwindow * window) {
    

    while (!glfwWindowShouldClose(window)) {
        double startTime = glfwGetTime();

        if (0 != game_tick()) {
             // HANDLE GAME TICK ERROR  
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (0 != render_tick()) {
             // HANDLE GAME TICK ERROR
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		while (elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
            elapsedTime = glfwGetTime() - startTime;
		}
    }
    return 0;
}