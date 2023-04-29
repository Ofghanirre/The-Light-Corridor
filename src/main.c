#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

#define PROJECT_NAME "The Light Corridor"
#define PROJECT_VERSION "v0.0.0"

#include "game.h"
#include "render.h"
#include "controller.h"

#include "test.h"
#include "parser.h"


int main(int argc, char const *argv[])
{
    test();
    printf("Launching " PROJECT_NAME " ~ " PROJECT_VERSION "!\n");
    //test_scenery();
    /* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;

    window = window_init();
    if (window == NULL) {
        glfwTerminate();
        return -1;
    }

    game_init();
    render_init();

    run_game(window);

    game_free();
    render_free();
    glfwTerminate();
    printf("Stopping  " PROJECT_NAME " ~ " PROJECT_VERSION "!\n");
    return 0;
}
