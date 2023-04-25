#include "render.h"
#include "controller.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

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
    gluLookAt(0., 0., 40., 0., 0., 0., 0., 1., 0.);

    // Lighting
    float position[4] = {0., 0., 5., 1.0};
    float intensity[3] = {1.5, 1.5, 1.5};
    float quadratic_attenuation = 0.0004;
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, intensity);
    glLightfv(GL_LIGHT0, GL_SPECULAR, intensity);
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &quadratic_attenuation);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // Start drawing

    // Draw corridor
    glBegin(GL_QUADS);
        glColor3f(1., 0., 0.);
        glNormal3f(0., 1., 0.);
        glVertex3f(-25., -15., 0.);
        glVertex3f(25., -15., 0.);
        glVertex3f(25., -15., -100.);
        glVertex3f(-25., -15., -100.);
        
        glNormal3f(0., -1., 0.);
        glVertex3f(25., 15., 0.);
        glVertex3f(-25., 15., 0.);
        glVertex3f(-25., 15., -100.);
        glVertex3f(25., 15., -100.);

        glColor3f(0.5, 0., 0.5);
        glNormal3f(1., 0., 0.);
        glVertex3f(-25., -15., 0.);
        glVertex3f(-25., 15., 0.);
        glVertex3f(-25., 15., -100.);
        glVertex3f(-25., -15., -100.);

        glNormal3f(-1., 0., 0.);
        glVertex3f(25., -15., 0.);
        glVertex3f(25., 15., 0.);
        glVertex3f(25., 15., -100.);
        glVertex3f(25., -15., -100.);
    glEnd();

    // Lines test
    glLineWidth(5);
    glColor3f(.5, .5, .5);
    glNormal3f(0., 0., 1.);
    for (int i = 0 ; i > -100 ; i -= 20) {
        glBegin(GL_LINE_LOOP);
            glVertex3f(-24.9, -14.9, i);
            glVertex3f(24.9, -14.9, i);
            glVertex3f(24.9, 14.9, i);
            glVertex3f(-24.9, 14.9, i);
        glEnd();

    }
    
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glFinish();

    return 0;
}