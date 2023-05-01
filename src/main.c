#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define PROJECT_NAME "The Light Corridor"
#define PROJECT_VERSION "v0.0.0"

#include "game.h"
#include "render.h"
#include "controller.h"

#include "test.h"

int Lflag = 0;
char *lvalue = NULL;
char * main_game_file_path = "./resources/levels/default.game";

static void args_parser(int argc, char * const *argv) {
    int c;

    while (1) {
        static struct option long_options[] = {
            {"L", no_argument, &Lflag, 1},
            {"l", required_argument, 0, 'l'},
            {"g", required_argument, 0, 'g'},
            {0, 0, 0, 0}
        };
        int option_index = 0;
        c = getopt_long(argc, argv, "Ll:g:", long_options, &option_index);
        if (c == -1) {
            break;
        }
        switch (c) {
            case 'L':
                set_logging();
                break;
            case 'l':
                set_logging();
                set_logging_file(optarg);
                break;
            case 'g':
                main_game_file_path = optarg;
                break;
            default:
                printf("Usage : -L -l [logging_file]\n\t-L : activate logging on stdout\n\t-l [logging_file] activate logging on a given logging_file\n\n");
                exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char const *argv[])
{
    args_parser(argc, (char* const*) argv);
    printf("Launching " PROJECT_NAME " ~ " PROJECT_VERSION "!\n");
    /* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;

    window = window_init();
    if (window == NULL) {
        glfwTerminate();
        return -1;
    }

    game_init(main_game_file_path);
    render_init();

    run_game(window);

    game_free();
    render_free();
    printf("Stopping  " PROJECT_NAME " ~ " PROJECT_VERSION "!\n");
    return 0;
}
