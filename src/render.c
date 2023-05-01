#include "render.h"
#include "controller.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdint.h>
#include "game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define NB_SEG_CIRCLE 64
#ifndef M_PI
#define M_PI 3.141
#endif

static textures_t textures;
static uint16_t fontMetrics[256];

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

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures.gl_texture[4]);
    glColor3f(0.146, 0.515, 0.860);
    glNormal3f(1., 0., 0.);

    double offset = fmod(-game_state.paddle_z_pos, 5) / 5;
    double start = offset, end = 1. + offset;
    for (double y = y1 ; y< y2 ; y += 5) {
        for (double z = 50 ; z > -200 ; z -= 5) { 
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(start, 0.); glVertex3f(x1, y, z);
                glTexCoord2f(start, 1.); glVertex3f(x1, y+5, z);
                glTexCoord2f(end, 1.); glVertex3f(x1, y+5, z-5);
                glTexCoord2f(end, 0.); glVertex3f(x1, y, z-5);
            glEnd();
        }
    }
        
    glNormal3f(-1., 0., 0.);
    for (double y = y1 ; y< y2 ; y += 5) {
        for (double z = 50 ; z > -200 ; z -= 5) { 
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(start, 0.); glVertex3f(x2, y, z);
                glTexCoord2f(start, 1.); glVertex3f(x2, y+5, z);
                glTexCoord2f(end, 1.); glVertex3f(x2, y+5, z-5);
                glTexCoord2f(end, 0.); glVertex3f(x2, y, z-5);
            glEnd();
        }
    }
    glDisable(GL_TEXTURE_2D);
        
    // Lines
    // glLineWidth(5);
    // glColor3f(1., 1., 1.);
    
    // for (double i = fmod(-game_state.paddle_z_pos, 20.); i > -200 ; i -= 20) {
    //     glBegin(GL_LINE_LOOP);
    //         glNormal3f(0., 1., 0.);
    //         glVertex3f(-24.9, -14.9, i);
    //         glVertex3f(24.9, -14.9, i);
    //         glNormal3f(-1., 0., 0.);
    //         glVertex3f(24.9, 14.9, i);
    //         glNormal3f(0., -1., 0.);
    //         glVertex3f(-24.9, 14.9, i);
    //         glNormal3f(1., 0., 0.);
    //     glEnd();
    // }
}

static void draw_paddle() {
    glMaterialfv(GL_FRONT, GL_SPECULAR, (float[]){0.01, 0.01, 0.01});
    glMaterialf(GL_FRONT, GL_SHININESS, 1.);
    if (game_state.glue_enabled) glColor4f(0.0140, 0.700, 0.243, 0.6);
    else glColor4f(0.7, 0.7, 0.7, 0.6);
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
    if (y1 < y2) { 
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
        
        glNormal3d(0., 0., 1.);
        double offset_x, offset_y;
        offset_x = x2 - x1 < 5 ? x2 - x1 : 5;
        offset_y = y1 - y2 < 5 ? y1 - y2 : 5;
        for (double x = x1 ; x < x2 ; x += 5) {
            for (double y = y2 ; y < y1 ; y += 5) {
                glBegin(GL_TRIANGLE_FAN);
                    glVertex3d(x, y, 0);
                    glVertex3d(x, y+offset_y, 0);
                    glVertex3d(x+offset_x, y+offset_y, 0);
                    glVertex3d(x+offset_x, y, 0);
                glEnd();
            }
        }
        
    glPopMatrix();
}

static void draw_graphic_object(Graphic_Object *obstacle) {
    switch(obstacle->figure.type) {
        case RECTANGLE : draw_rectangle(obstacle); break;
        case SPHERE: draw_sphere(obstacle); break;
        case CIRCLE: draw_circle(obstacle); break;
        case LABEL: break;
    }
}

static void draw_obstacles() {
    Node *obstacle = game_state.level.obstacles.tail;
    for (; obstacle != NULL ; obstacle = obstacle->prev) {
        draw_graphic_object(&(obstacle->elem));
    }
}

static void draw_bonus() {
    static float glowing_effect_iter = 0.0;
    static float glowing_effect_factor = 1.0;
    Node *bonus = game_state.level.bonus.tail;
    for (; bonus != NULL ; bonus = bonus->prev) {
        // draw_graphic_object(&(bonus->elem));
        Graphic_Object glowing = (Graphic_Object){bonus->elem.position, bonus->elem.orientation, bonus->elem.figure, bonus->elem.effect};
        glowing.figure.color.r += glowing_effect_iter;
        glowing.figure.color.g += glowing_effect_iter;
        glowing.figure.color.b += glowing_effect_iter;
        draw_graphic_object(&(glowing));
    }
    glowing_effect_iter += 0.1 * glowing_effect_factor;
    if (fabs(glowing_effect_iter) >= 0.8) {
        glowing_effect_factor *= -1.0;
    }
}

#define BITMAP_STEP 0.0625
#define BASE_CHAR_SIZE 0.1
// Draws a character from a fontmap with given line and column, must have the fontmap texture loaded already
// The character is drawn on origin (top right corner), according to BASE_CHAR_SIZE
static void drawFromFontmap(int i, int j) {
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(j*BITMAP_STEP, (i+1)*BITMAP_STEP); glVertex2f(0., BASE_CHAR_SIZE);
        glTexCoord2f(j*BITMAP_STEP, i*BITMAP_STEP); glVertex2f(0., 0.);
        glTexCoord2f((j+1)*BITMAP_STEP, i*BITMAP_STEP); glVertex2f(BASE_CHAR_SIZE, 0.);
        glTexCoord2f((j+1)*BITMAP_STEP, (i+1)*BITMAP_STEP); glVertex2f(BASE_CHAR_SIZE, BASE_CHAR_SIZE);
    glEnd();
}

// Draws a string with the origin as top left corner, with base character size (0.1)
static float drawString(char string[]) {
    float offset = 0;
    glBindTexture(GL_TEXTURE_2D, textures.gl_texture[0]);
    for (char *c = string; *c != '\0'; c++) {
        drawFromFontmap(*c / 16, *c % 16);
        float width = fontMetrics[(int)*c] / 128. * BASE_CHAR_SIZE;
        offset += width;
        glTranslatef(width, 0., 0.);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    return offset;
}

static void load_textures() {
    // Allows to load textures of any sizes (not requiring powers of 2)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

    glGenTextures(NB_TEXTURES, textures.gl_texture);

    const char *texture_files[] = {"resources/textures/fontmap.tga", "resources/textures/life.tga", 
    "resources/textures/title_screen.tga", "resources/textures/game_over.tga",
    "resources/textures/wall.tga"};
    int x, y, n;

    for (int i = 0 ; i < NB_TEXTURES ; i++) {
        textures.data[i] = stbi_load(texture_files[i], &x, &y, &n, 0);
        if (textures.data[i] == NULL) {
            fprintf(stderr, "Texture %d failed to load", i);
            exit(1);
        }
        glBindTexture(GL_TEXTURE_2D, textures.gl_texture[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textures.data[i]);
    }
	glBindTexture(GL_TEXTURE_2D, 0);
}

static void free_textures() {
    for (int i = 0 ; i < NB_TEXTURES ; i++) {
        stbi_image_free(textures.data[0]);
    }
}

static void load_font_metrics() {
    FILE *file = fopen("resources/font_metrics.dat", "rb");
    if (file == NULL) {
        fprintf(stderr, "Couldn't load font metrics, this will cause issues\n");
        return;
    }
    if (fread(fontMetrics, sizeof(uint16_t), 256, file) != 256) {
        fprintf(stderr, "Couldn't load font metrics properly, this will cause issues\n");
    }
    fclose(file);
}

static void draw_level_info() {
    glPushMatrix();
        glColor3f(1., 1., 1.);
        glScalef(0.5, 0.5, 0.5);
        glPushMatrix();
            glTranslatef(0.05, 0.05, 0.);
            drawString(game_state.level.name);
        glPopMatrix();
        glTranslatef(0.05, 0.15, 0.0);
        glScalef(0.75, 0.75, 0.75);
        char position[64];
        sprintf(position, "%f", game_state.paddle_z_pos );
        drawString(position);
    glPopMatrix();
}

static void draw_life_counter() {
    glPushMatrix();
        glTranslatef(0.05, 0.88, 0.);
        glColor3f(1., 1., 1.);
        drawString("Lives:");
        glBindTexture(GL_TEXTURE_2D, textures.gl_texture[1]);
        glColor3f(1., 1., 1.);
        for (int i = 0 ; i < game_state.lives ; i++) {
            glBegin(GL_QUADS);
                glTexCoord2f(0., 1.); glVertex2f(0., BASE_CHAR_SIZE);
                glTexCoord2f(0., 0.); glVertex2f(0., 0.);
                glTexCoord2f(1., 0.); glVertex2f(BASE_CHAR_SIZE, 0.);
                glTexCoord2f(1., 1.); glVertex2f(BASE_CHAR_SIZE, BASE_CHAR_SIZE);
            glEnd();
            glTranslatef(BASE_CHAR_SIZE / 2., 0., 0.);
        }
        glBindTexture(GL_TEXTURE_2D, textures.gl_texture[0]);
    glPopMatrix();
}

static void draw_glue_bonus() {
    float width = aspectRatio > 0 ? aspectRatio : 1.0;

    static float max_glue_value = 0;
    if (game_state.glue_enabled > max_glue_value) {
        max_glue_value = game_state.glue_enabled;
    }
    glPushMatrix();
        glTranslatef(width - 0.6, 0.88, 0.);
        glColor3f(1., 1., 1.);
        drawString("Glue:");
        glBindTexture(GL_TEXTURE_2D, textures.gl_texture[1]);
        glColor3f(0.8, 0.8, 0.8);
        glTranslatef(0.0, 0.0275, 0.);

        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0., 0., 0.);
            glVertex3f(0.3,0.,0.0);
            glVertex3f(0.3,0.05,0.0);
            glVertex3f(0.0,0.05,0.0);
	    glEnd();
        glColor3f(1.0, 1.0, 1.0);
        float percentage = 0.0;
        if (game_state.glue_enabled == TIMELESS_GLUE) percentage = 1.0;
        else {
            percentage = game_state.glue_enabled / max_glue_value;
        }
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0., 0., 0.);
            glVertex3f(0.3*percentage,0.0,0.0);
            glVertex3f(0.3*percentage,0.05,0.0);
            glVertex3f(0.0,0.05,0.0);
	    glEnd();

        glBindTexture(GL_TEXTURE_2D, textures.gl_texture[0]);
    glPopMatrix();
}

static void draw_new_level() {
    if (game_state.paddle_z_pos <= TRANSITION_LEVEL_DISTANCE && game_state.paddle_z_pos >= 0) {
        glPushMatrix();
            glColor3f(1., 1., 1.);
            glTranslatef(0.4, 0.5, 0.5);
            drawString("-*- NEW LEVEL -*-");
        glPopMatrix();
    }
}

static void draw_game_HUD() {
    glDepthMask(GL_FALSE); 
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    if (aspectRatio > 0) {
        gluOrtho2D(0.0, 1.0 * aspectRatio, 1.0, 0.0);
    } else {
        gluOrtho2D(0.0, 1.0, 1.0 * aspectRatio, 0.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    
    // Draw Level Info
    draw_level_info();

    // Draw life counter
    draw_life_counter();

    // New level info
    draw_new_level();

    // Bonus Glue info
    if (game_state.glue_enabled) draw_glue_bonus();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glDepthMask(GL_TRUE); 
}

static void draw_game_scene() {
    // Set up 3D projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
	glLoadIdentity();
    gluPerspective(60.0, aspectRatio, 1, 200);

    // Set up modelview matrix
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
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
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    float position_0[4] = {0., 0., 30., 1.0};
    float intensity_0[3] = {.8, .8, .8};
    float quadratic_attenuation_0 = 0.00005;
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
        draw_bonus();
    glPopMatrix();

    // Draw paddle after opaque objects, for transparency to work!
    glPushMatrix();
        glTranslated(game_state.paddle.position.x, game_state.paddle.position.y, PADDLE_Z);
        draw_paddle();
    glPopMatrix();
    
    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    

    // Restore modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // Restore projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

static void draw_title_screen() {
    glDepthMask(GL_FALSE); 
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    float width = 1.0, height = 1.0;

    if (aspectRatio > 0) {
        width = aspectRatio;
        gluOrtho2D(0.0, 1.0 * aspectRatio, 1.0, 0.0);
    } else {
        height = aspectRatio;
        gluOrtho2D(0.0, 1.0, 1.0 * aspectRatio, 0.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, textures.gl_texture[2]);
    // Draw now
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0., 1.); glVertex3f(0., height, 0.);
        glTexCoord2f(1., 1.); glVertex3f(width, height, 0.);
        glTexCoord2f(1., 0.); glVertex3f(width, 0., 0.);
        glTexCoord2f(0., 0.); glVertex3f(0., 0., 0.);
    glEnd();

    glPushMatrix();
        glTranslatef(0.553 * width, 0.633 * height, 0.);
        glScalef(0.7, 0.7, 1.);
        glColor3f(1., 1., 1.);

        char level_number_string[8];
        snprintf(level_number_string, 8, "%d", game_state.level_selected);
        drawString(level_number_string);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glDepthMask(GL_TRUE); 
}

static void draw_game_over() {
    glDepthMask(GL_FALSE); 
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    float width = 1.0, height = 1.0;

    if (aspectRatio > 0) {
        width = aspectRatio;
        gluOrtho2D(0.0, 1.0 * aspectRatio, 1.0, 0.0);
    } else {
        height = aspectRatio;
        gluOrtho2D(0.0, 1.0, 1.0 * aspectRatio, 0.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, textures.gl_texture[3]);
    // Draw now
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0., 1.); glVertex3f(0., height, 0.);
        glTexCoord2f(1., 1.); glVertex3f(width, height, 0.);
        glTexCoord2f(1., 0.); glVertex3f(width, 0., 0.);
        glTexCoord2f(0., 0.); glVertex3f(0., 0., 0.);
    glEnd();

    glPushMatrix();
        glTranslatef(0.25 * width, 0.4 * height, 0.);
        glScalef(0.7, 0.7, 1.);
        glColor3f(1., 1., 1.);

        if (game_state.lives <= 1) drawString("You ran out of lives!");
        else drawString("Congratulations, you won!");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.5 * width, 0.62 * height, 0.);
        glColor3f(1., 1., 1.);


        char score_string[32];
        snprintf(score_string, 32, "%ld", (long) game_state.score);
        drawString(score_string);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glDepthMask(GL_TRUE); 
}

void render_init() {
    printf("Render init\n");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    load_textures();
    load_font_metrics();
    printf("Loaded textures\n");
}

void render_free() {
    printf("Render free\n");
    free_textures();
    glfwTerminate();
}

int render_tick() {
    switch (game_state.scene) {
        case TITLE_SCREEN:
            draw_title_screen();
            break;
        case GAME:
            draw_game_scene();
            draw_game_HUD();
            break;
        case GAME_OVER:
            draw_game_over();
            break;
    }    

    return 0;
}
