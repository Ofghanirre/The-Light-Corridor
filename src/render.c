#include "render.h"
#include "controller.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

static void draw_corridor() {
    float x1, x2, y1, y2;
    x1 = -CORRIDOR_WIDTH / 2;
    x2 = CORRIDOR_WIDTH / 2;
    y1 = -CORRIDOR_HEIGHT / 2;
    y2 = CORRIDOR_HEIGHT / 2;

    glBegin(GL_QUADS);
        glColor3f(1., 0., 0.);
        glNormal3f(0., 1., 0.);
        glVertex3f(x1, y1, 50.);
        glVertex3f(x2, y1, 50.);
        glVertex3f(x2, y1, -200.);
        glVertex3f(x1, y1, -200.);
        
        glNormal3f(0., -1., 0.);
        glVertex3f(x2, y2, 50.);
        glVertex3f(x1, y2, 50.);
        glVertex3f(x1, y2, -200.);
        glVertex3f(x2, y2, -200.);

        glColor3f(0.5, 0., 0.5);
        glNormal3f(1., 0., 0.);
        glVertex3f(x1, y1, 50.);
        glVertex3f(x1, y2, 50.);
        glVertex3f(x1, y2, -200.);
        glVertex3f(x1, y1, -200.);

        glNormal3f(-1., 0., 0.);
        glVertex3f(x2, y1, 50.);
        glVertex3f(x2, y2, 50.);
        glVertex3f(x2, y2, -200.);
        glVertex3f(x2, y1, -200.);
    glEnd();

    // Lines test
    glLineWidth(5);
    glColor3f(.5, .5, .5);
    glNormal3f(0., 0., 1.);
    for (double i = fmod(game_state.camera_pos, 20.); i > -200 ; i -= 20) {
        glBegin(GL_LINE_LOOP);
            glVertex3f(-24.9, -14.9, i);
            glVertex3f(24.9, -14.9, i);
            glVertex3f(24.9, 14.9, i);
            glVertex3f(-24.9, 14.9, i);
        glEnd();
    }
}

static void draw_paddle() {
    glColor3f(1., 1., 1.);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-PADDLE_WIDTH / 2, -PADDLE_HEIGHT / 2, 0);
        glVertex3f(-PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2, 0);
        glVertex3f(PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2, 0);
        glVertex3f(PADDLE_WIDTH / 2, -PADDLE_HEIGHT / 2, 0);
    glEnd();
}

static void draw_ball() {
    glColor3f(0.5, 0.5, 0.5);
    gluSphere(gluNewQuadric(), BALL_RADIUS, 64, 64);
}

void render_init() {
    printf("Render init\n");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void render_free() {
    printf("Render free\n");
}

int render_tick() {    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Camera setup
    gluLookAt(0., 0., 30., 0., 0., 0., 0., 1., 0.);

    // Lighting
    float position[4] = {0., 0., 40., 1.0};
    float intensity[3] = {3., 3., 3.};
    float quadratic_attenuation = 0.001;
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, intensity);
    glLightfv(GL_LIGHT0, GL_SPECULAR, intensity);
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &quadratic_attenuation);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // Start drawing
    draw_corridor();

    glPushMatrix();
        glTranslated(game_state.paddle.position.x, game_state.paddle.position.y, PADDLE_Z);
        draw_paddle();
    glPopMatrix();

    glPushMatrix();
        glTranslated(game_state.ball.position.x, game_state.ball.position.y, game_state.ball.position.z);
        draw_ball();
    glPopMatrix();
    
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glFinish();
    return 0;
}
