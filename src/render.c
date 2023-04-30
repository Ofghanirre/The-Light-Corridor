#include "render.h"
#include "controller.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#define NB_SEG_CIRCLE 64
#ifndef M_PI
#define M_PI 3.141
#endif

static void draw_corridor() {
    float x1, x2, y1, y2;
    x1 = -CORRIDOR_WIDTH / 2;
    x2 = CORRIDOR_WIDTH / 2;
    y1 = -CORRIDOR_HEIGHT / 2;
    y2 = CORRIDOR_HEIGHT / 2;

    glMaterialfv(GL_FRONT, GL_SPECULAR, (float[]){0., 0., 0});
    glMaterialf(GL_FRONT, GL_SHININESS, 0.);
    

    // need subdividing the surfaces so that lighting looks okay
    glColor3f(0.118, 0.382, 0.840);
    glNormal3f(0., 1., 0.);
    for (double x = x1 ; x < x2 ; x += 5) {
        for (double z = 50 ; z > -200 ; z -= 5) { 
            glBegin(GL_TRIANGLE_FAN);
                glVertex3f(x, y1, z);
                glVertex3f(x+5, y1, z);
                glVertex3f(x+5, y1, z + 5);
                glVertex3f(x, y1, z + 5);
            glEnd();
        }
    }
 
    glNormal3f(0., -1., 0.);
    for (double x = x1 ; x < x2 ; x += 5) {
        for (double z = 50 ; z > -200 ; z -= 5) { 
            glBegin(GL_TRIANGLE_FAN); 
                glVertex3f(x+5, y2, z);
                glVertex3f(x, y2, z);
                glVertex3f(x, y2, z-5);
                glVertex3f(x+5, y2, z-5);
            glEnd();
        }
    }

    glColor3f(0.146, 0.515, 0.860);
    glNormal3f(1., 0., 0.);
    for (double y = y1 ; y< y2 ; y += 5) {
        for (double z = 50 ; z > -200 ; z -= 5) { 
            glBegin(GL_TRIANGLE_FAN);
                glVertex3f(x1, y, z);
                glVertex3f(x1, y+5, z);
                glVertex3f(x1, y+5, z-5);
                glVertex3f(x1, y, z-5);
            glEnd();
        }
    }
        
    glNormal3f(-1., 0., 0.);
    for (double y = y1 ; y< y2 ; y += 5) {
        for (double z = 50 ; z > -200 ; z -= 5) { 
            glBegin(GL_TRIANGLE_FAN);
                glVertex3f(x2, y, z);
                glVertex3f(x2, y+5, z);
                glVertex3f(x2, y+5, z-5);
                glVertex3f(x2, y, z-5);
            glEnd();
        }
    }
        
    // Lines
    glLineWidth(5);
    glColor3f(1., 1., 1.);
    
    for (double i = fmod(-game_state.paddle_z_pos, 20.); i > -200 ; i -= 20) {
        glBegin(GL_LINE_LOOP);
            glNormal3f(0., 1., 0.);
            glVertex3f(-24.9, -14.9, i);
            glVertex3f(24.9, -14.9, i);
            glNormal3f(-1., 0., 0.);
            glVertex3f(24.9, 14.9, i);
            glNormal3f(0., -1., 0.);
            glVertex3f(-24.9, 14.9, i);
            glNormal3f(1., 0., 0.);
        glEnd();
    }
}

static void draw_paddle() {
    glMaterialfv(GL_FRONT, GL_SPECULAR, (float[]){0.01, 0.01, 0.01});
    glMaterialf(GL_FRONT, GL_SHININESS, 1.);
    glColor4f(0.0140, 0.700, 0.243, 0.6);
    glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0, 0, 1);
        glVertex3f(-PADDLE_WIDTH / 2, -PADDLE_HEIGHT / 2, 0);
        glVertex3f(-PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2, 0);
        glVertex3f(PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2, 0);
        glVertex3f(PADDLE_WIDTH / 2, -PADDLE_HEIGHT / 2, 0);
    glEnd();
}

static void draw_base_ball() {
    glMaterialfv(GL_FRONT, GL_SPECULAR, (float[]){.8, .8, .8});
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

static void draw_sphere(Graphic_Object *obstacle) {
    double alpha = 1.;
    if (game_state.paddle_z_pos - obstacle->position.z < 0.1) { 
        return;
    }
    if (game_state.paddle_z_pos - obstacle->position.z < 20) {
        alpha = (game_state.paddle_z_pos - obstacle->position.z) / 20 + 0.5;
    }
    glNormal3d(0, 0, 1);

    glPushMatrix();
        glTranslated(obstacle->position.x, obstacle->position.y, obstacle->position.z);
        glMaterialfv(GL_FRONT, GL_SPECULAR, (float[]){.8, .8, .8});
        glMaterialf(GL_FRONT, GL_SHININESS, 16.);
        glColor4d(obstacle->figure.color.r,obstacle->figure.color.g,obstacle->figure.color.b, alpha);
        gluSphere(gluNewQuadric(), obstacle->figure.fig.sphere.radius, 64, 64);
    glPopMatrix();
}

static void draw_circle(Graphic_Object *obstacle) {
    double alpha = 1.;
    if (game_state.paddle_z_pos - obstacle->position.z < 0.1) { 
        return;
    }
    if (game_state.paddle_z_pos - obstacle->position.z < 20) {
        alpha = (game_state.paddle_z_pos - obstacle->position.z) / 20 + 0.5;
    }
    glNormal3d(0, 0, 1);
    glPushMatrix();
        glTranslated(obstacle->position.x, obstacle->position.y, obstacle->position.z);
        glMaterialfv(GL_FRONT, GL_SPECULAR, (float[]){0.01, 0.01, 0.01});
        glMaterialf(GL_FRONT, GL_SHININESS, 1.);
        glBegin(GL_TRIANGLE_FAN);
            glColor4d(obstacle->figure.color.r,obstacle->figure.color.g,obstacle->figure.color.b, alpha);
            glVertex3f(0.0,0.0,0.0);
            float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
            for(int i=0;i<=NB_SEG_CIRCLE;i++) {
                glVertex3f(cos(i*step_rad)*obstacle->figure.fig.circle.radius,sin(i*step_rad)*obstacle->figure.fig.circle.radius,0.0f);
            }
        glEnd();
    glPopMatrix();
}
static void draw_rectangle(Graphic_Object *obstacle) {
    /* Here we assume obstacles are necessarily flat rectangles facing the camera.
    The structure for Graphic_Object can allow for more flexibility but we leave it at that
    */
    double x1 = obstacle->figure.fig.rectangle.p1.x;
    double x2 = obstacle->figure.fig.rectangle.p2.x;
    double y1 = obstacle->figure.fig.rectangle.p1.y;
    double y2 = obstacle->figure.fig.rectangle.p2.y;
    double alpha = 1.;

    if (x1 > x2) { 
        double temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (y1 > y2) { 
        double temp = y1;
        y1 = y2;
        y2 = temp;
    }

    if (game_state.paddle_z_pos - obstacle->position.z < 0.1) { 
        return;
    }
    if (game_state.paddle_z_pos - obstacle->position.z < 20) {
        alpha = (game_state.paddle_z_pos - obstacle->position.z) / 20 + 0.5;
    }

    glPushMatrix();
        glTranslated(obstacle->position.x, obstacle->position.y, obstacle->position.z);

        glMaterialfv(GL_FRONT, GL_SPECULAR, (float[]){0.01, 0.01, 0.01});
        glMaterialf(GL_FRONT, GL_SHININESS, 1.);
        glColor4d(obstacle->figure.color.r, obstacle->figure.color.g, obstacle->figure.color.b, alpha);
        
        glNormal3d(0, 0, 1);
        for (double x = x1 ; x < x2 ; x += 5) {
            for (double y = y1 ; y < y2 ; y += 5) {
                glBegin(GL_TRIANGLE_FAN);
                    glVertex3d(x, y, 0);
                    glVertex3d(x, y+5, 0);
                    glVertex3d(x+5, y+5, 0);
                    glVertex3d(x+5, y, 0);
                glEnd();
            }
        }
        
    glPopMatrix();
}

static void draw_obstacle(Graphic_Object *obstacle) {
    switch(obstacle->figure.type) {
        case RECTANGLE : draw_rectangle(obstacle); break;
        case SPHERE: draw_sphere(obstacle); break;
        case CIRCLE: draw_circle(obstacle); break;
        case LABEL: break;
    }
}

static void draw_obstacles() {
    Node *obstacle = game_state.level.obstacles.head;
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
    glfwTerminate();
}

int render_tick() {    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Camera setup
    gluLookAt(0., 0., CAMERA_OFFSET, 0., 0., 0., 0., 1., 0.);

    // glColor is used for ambient and diffuse lighting
    glEnable(GL_COLOR_MATERIAL);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    GLfloat lmodel_ambient[] = { 0.01, 0.01, 0.01, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    
    // Camera light
    float position_0[4] = {0., 0., 30., 1.0};
    float intensity_0[3] = {.8, .8, .8};
    float quadratic_attenuation_0 = 0.00005;
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, position_0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, intensity_0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, intensity_0);
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &quadratic_attenuation_0);

    // Ball light
    glEnable(GL_LIGHT1);
    glPushMatrix();
        glTranslated(0., 0., -game_state.paddle_z_pos);
        glTranslated(game_state.ball.position.x, game_state.ball.position.y, game_state.ball.position.z);
        float position_1[4] = {0., 0., 0., 1.0};
        float intensity_1[3] = {.5, .5, .5};
        float quadratic_attenuation_1 = 0.001;
        
        glLightfv(GL_LIGHT1, GL_POSITION, position_1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, intensity_1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, intensity_1);
        glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, &quadratic_attenuation_1);
    glPopMatrix();
    
    // Start drawing

    // Draw corridor
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
