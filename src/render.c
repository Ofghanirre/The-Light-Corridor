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
        glMaterialfv(GL_FRONT, GL_SPECULAR, (float[]){0.01, 0.01, 0.01});
        glMaterialf(GL_FRONT, GL_SHININESS, 1.);
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
    for (double i = fmod(-game_state.paddle_z_pos, 20.); i > -200 ; i -= 20) {
        glBegin(GL_LINE_LOOP);
            glVertex3f(-24.9, -14.9, i);
            glVertex3f(24.9, -14.9, i);
            glVertex3f(24.9, 14.9, i);
            glVertex3f(-24.9, 14.9, i);
        glEnd();
    }
}

static void draw_paddle() {
    glMaterialfv(GL_FRONT, GL_SPECULAR, (float[]){0.01, 0.01, 0.01});
    glMaterialf(GL_FRONT, GL_SHININESS, 1.);
    glColor4f(0.00710, 0.277, 0.710, 0.6);
    glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0, 0, 1);
        glVertex3f(-PADDLE_WIDTH / 2, -PADDLE_HEIGHT / 2, 0);
        glVertex3f(-PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2, 0);
        glVertex3f(PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2, 0);
        glVertex3f(PADDLE_WIDTH / 2, -PADDLE_HEIGHT / 2, 0);
    glEnd();
}

static void draw_base_ball() {
    glMaterialfv(GL_FRONT, GL_SPECULAR, (float[]){1., 1., 1.});
    glMaterialf(GL_FRONT, GL_SHININESS, 16.);
    glColor3f(0.5, 0.5, 0.5);
    gluSphere(gluNewQuadric(), BALL_RADIUS, 64, 64);
}

static void draw_ball() {
    glPushMatrix();
        glTranslated(game_state.ball.position.x, game_state.ball.position.y, game_state.ball.position.z);
        draw_base_ball();
    glPopMatrix();
}

static void draw_obstacle(Graphic_Object *obstacle) {
    /* Here we assume obstacles are necessarily flat rectangles facing the camera.
    The structure for Graphic_Object can allow for more flexibility but we leave it at that
    */
    double x1 = obstacle->figure.fig.rectangle.p1.x;
    double x2 = obstacle->figure.fig.rectangle.p2.x;
    double y1 = obstacle->figure.fig.rectangle.p1.y;
    double y2 = obstacle->figure.fig.rectangle.p2.y;

    if (game_state.paddle_z_pos - obstacle->position.z < 0) { 
        return;
    }

    glPushMatrix();
        glTranslated(obstacle->position.x, obstacle->position.y, obstacle->position.z);

        glMaterialfv(GL_FRONT, GL_SPECULAR, (float[]){0.01, 0.01, 0.01});
        glMaterialf(GL_FRONT, GL_SHININESS, 1.);
        glColor3d(obstacle->figure.color.r, obstacle->figure.color.g, obstacle->figure.color.b);
        
        glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0, 0, 1);
        glVertex3d(x1, y1, 0);
        glVertex3d(x1, y2, 0);
        glVertex3d(x2, y2, 0);
        glVertex3d(x2, y1, 0);
        glEnd();

    glPopMatrix();
}

static void draw_obstacles() {
    Node *obstacle = game_state.scenery.obstacles.head;
    for (; obstacle != NULL ; obstacle = obstacle->next) {
        draw_obstacle(&(obstacle->elem));
    }
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
    gluLookAt(0., 0., CAMERA_OFFSET, 0., 0., 0., 0., 1., 0.);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    // Lighting
    float position[4] = {0., 0., 40., 1.0};
    float intensity[3] = {2.5, 2.5, 2.5};
    float quadratic_attenuation = 0.001;
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, intensity);
    glLightfv(GL_LIGHT0, GL_SPECULAR, intensity);
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &quadratic_attenuation);

    // Set material properties
    glEnable(GL_COLOR_MATERIAL);

    // Start drawing

    // Draw corridor first
    draw_corridor();

    // Ball, obstacles and walls must be translated according to how far into the level we are
    glPushMatrix();
        glTranslated(0., 0., -game_state.paddle_z_pos);
        draw_ball();
        draw_obstacles();
    glPopMatrix();

    // Draw paddle after opaque objects, for transparency to work!
    glPushMatrix();
        glTranslated(game_state.paddle.position.x, game_state.paddle.position.y, PADDLE_Z);
        draw_paddle();
    glPopMatrix();
    
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glDisable(GL_BLEND);

    glFinish();
    return 0;
}
