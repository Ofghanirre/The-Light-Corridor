#include "game.h"
#include "controller.h"
#include "structs/vectors.h"
#include "level.h"
#include <stdio.h>
#include <math.h>
#include "cparser.h"

#ifndef M_PI
#define M_PI 3.141
#endif

/**
 * Modifies the ball's velocity vector as if it bounced off a surface with
 * the given normal vector
*/
void static ball_bounce(Vec3D normal) {
    double dot = dot_Vec3D(game_state.ball.direction, normal);
    game_state.ball.direction = normalize_Vec3D(sum_Vec3D(game_state.ball.direction, mul_Vec3D(normal, -2 * dot)));
}

void static ball_detect_wall_collision() {
    if (game_state.ball.position.x - BALL_RADIUS < -CORRIDOR_WIDTH / 2) {
        game_state.ball.position.x = -CORRIDOR_WIDTH / 2 + BALL_RADIUS;
        ball_bounce((Vec3D){1., 0., 0.});
    }
    if (game_state.ball.position.x + BALL_RADIUS > CORRIDOR_WIDTH / 2) {
        game_state.ball.position.x = CORRIDOR_WIDTH / 2 - BALL_RADIUS;
        ball_bounce((Vec3D){-1., 0., 0.});
    }
    if (game_state.ball.position.y - BALL_RADIUS < -CORRIDOR_HEIGHT / 2) {
        game_state.ball.position.y = -CORRIDOR_HEIGHT / 2 + BALL_RADIUS;
        ball_bounce((Vec3D){0., 1., 0.});
    }
    if (game_state.ball.position.y + BALL_RADIUS > CORRIDOR_HEIGHT / 2) {
        game_state.ball.position.y = CORRIDOR_HEIGHT / 2 - BALL_RADIUS;
        ball_bounce((Vec3D){0., -1., 0.});
    }
}

// Returns 1 if the ball failed to be caught
int static ball_detect_paddle_collision() {
    // We only consider paddle collision is the ball is heading towards it
    //if (game_state.ball.direction.z < 0) { return 0;}

    // The ball is still too far from the paddle
    if (game_state.ball.position.z + BALL_RADIUS <= 0 + game_state.paddle_z_pos) {
        return 0;
    }

    // We ball passed the paddle
    if (game_state.ball.position.z > 0 + game_state.paddle_z_pos) {
        return 1;
    }
    
    if (game_state.ball.position.x > game_state.paddle.position.x - PADDLE_WIDTH / 2 - BALL_RADIUS / 2
        && game_state.ball.position.x < game_state.paddle.position.x + PADDLE_WIDTH / 2 + BALL_RADIUS / 2
        && game_state.ball.position.y > game_state.paddle.position.y - PADDLE_WIDTH / 2 - BALL_RADIUS / 2
        && game_state.ball.position.y < game_state.paddle.position.y + PADDLE_WIDTH / 2 + BALL_RADIUS / 2) {
            Vec3D point_impact = (Vec3D){game_state.ball.position.x, game_state.ball.position.y, 0};
            Vec3D center = (Vec3D){game_state.paddle.position.x, game_state.paddle.position.y, 0};
            Vec3D impact = sum_Vec3D(point_impact, mul_Vec3D(center, -1));

            double max_angle = M_PI / 5;
            double x_theta = impact.x / (PADDLE_WIDTH / 2) * max_angle;
            double y_theta = impact.y / (PADDLE_HEIGHT / 2) * max_angle;

            Vec3D base_direction = (Vec3D){0., 0., -1.};

            game_state.ball.direction = rotate_x(rotate_y(base_direction, -x_theta), y_theta);
            game_state.ball.position.z = PADDLE_Z - BALL_RADIUS - 0.5 + game_state.paddle_z_pos;

            if (game_state.glue_enabled) {
                game_state.ball.glued = 1;
                game_state.ball.glued_offset.x = game_state.ball.position.x - game_state.paddle.position.x;
                game_state.ball.glued_offset.y = game_state.ball.position.y - game_state.paddle.position.y;
            }
        }
    return 0;
}

#define BOUNCE 1
#define NO_BOUNCE 0

int static obstacle_ball_bounce(double z_distance) {
    Vec3D normal;
    double offset;
    if (z_distance > 0) {
        // Ball hit from the front
        if (game_state.ball.direction.z > 0) return NO_BOUNCE;
        normal = (Vec3D){0., 0., 1.};
        offset = BALL_RADIUS - z_distance;
    } else {
        // Ball hit from the back
        if (game_state.ball.direction.z < 0) return NO_BOUNCE;
        normal = (Vec3D){0., 0., -1.};
        offset = -BALL_RADIUS - z_distance;
    }
    game_state.ball.position.z += offset;
    ball_bounce(normal);
    return BOUNCE;
}

int static ball_detect_rectangle(Graphic_Object *obstacle) {
    double z_distance = game_state.ball.position.z - obstacle->position.z;
    if (fabs(z_distance) > BALL_RADIUS) {
        return NO_BOUNCE;
    }

    double x1 = obstacle->figure.fig.rectangle.p1.x + obstacle->position.x;
    double x2 = obstacle->figure.fig.rectangle.p2.x + obstacle->position.x;
    double y1 = obstacle->figure.fig.rectangle.p1.y + obstacle->position.y;
    double y2 = obstacle->figure.fig.rectangle.p2.y + obstacle->position.y;

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

    if (game_state.ball.position.x > x1 - BALL_RADIUS / 2 && game_state.ball.position.x < x2 + BALL_RADIUS / 2 
        && game_state.ball.position.y > y1 - BALL_RADIUS / 2 && game_state.ball.position.y < y2 + - BALL_RADIUS / 2) {
        return obstacle_ball_bounce(z_distance);
    }
    return NO_BOUNCE;
}

int static ball_detecte_circle(Graphic_Object * obstacle) {
    double z_distance = game_state.ball.position.z - obstacle->position.z;
    if (fabs(z_distance) > BALL_RADIUS) {
        return NO_BOUNCE;
    }

    float distance_carre = (game_state.ball.position.x - obstacle->position.x) * (game_state.ball.position.x - obstacle->position.x) 
                            + (game_state.ball.position.y - obstacle->position.y) * (game_state.ball.position.y - obstacle->position.y);
    if (distance_carre - obstacle->figure.fig.circle.radius <= obstacle->figure.fig.circle.radius * obstacle->figure.fig.circle.radius) { // Collision détectée !
        return obstacle_ball_bounce(z_distance);
    }
    return NO_BOUNCE;
}

int static ball_detecte_sphere(Graphic_Object * obstacle) {
    double distance_centre = distance_Vec3D(obstacle->position, game_state.ball.position);
    if (distance_centre <= (obstacle->figure.fig.sphere.radius + BALL_RADIUS)) {
        return BOUNCE;
    }
    return NO_BOUNCE;
}

int static ball_detect_obstacle(Graphic_Object *obstacle) {
    switch(obstacle->figure.type) {
        case RECTANGLE : return ball_detect_rectangle(obstacle);
        case SPHERE: return ball_detecte_sphere(obstacle); // NO BOUNCE
        case CIRCLE: return ball_detecte_circle(obstacle);
        case LABEL: return NO_BOUNCE;
    }
    return NO_BOUNCE;
}

void static ball_detect_obstacles() {
    Node *obstacle = game_state.level.obstacles.head;
    for (; obstacle != NULL ; obstacle = obstacle->next) {
        ball_detect_obstacle(&(obstacle->elem));
    }
}

void static ball_detect_back() {
    if (game_state.ball.position.z < game_state.paddle_z_pos - BACK_DISTANCE) {
        ball_bounce((Vec3D){0., 0., 1.});
    }
}

void static ball_detect_end_level() {
    if (game_state.paddle_z_pos < - game_state.level.depth) {
        printf("End level\n");
        level_clear(&(game_state.level));
        loader_next_level(&(game_state.level), &(game_state.levelLoader));
        float distance = game_state.ball.position.z - game_state.paddle_z_pos;
        game_state.paddle_z_pos = fmod(game_state.paddle_z_pos, 20.) + TRANSITION_LEVEL_DISTANCE*2;
        game_state.ball.position.z = game_state.paddle_z_pos + distance;
    }
}

void static ball_tick() {
    if (game_state.ball.glued != 0) {
        game_state.ball.position.x = game_state.paddle. position.x + game_state.ball.glued_offset.x;
        game_state.ball.position.y = game_state.paddle.position.y + game_state.ball.glued_offset.y;
        game_state.ball.position.z = game_state.paddle_z_pos - PADDLE_Z - BALL_RADIUS;
        return;
    }

    game_state.ball.position = sum_Vec3D(game_state.ball.position, mul_Vec3D(game_state.ball.direction, game_state.ball.speed));
    ball_detect_wall_collision();
    ball_detect_obstacles();
    ball_detect_back();
    int lost_ball = ball_detect_paddle_collision();
    
    if (lost_ball) {
        printf("You lost the ball!\n");
        game_state.lives -= 1;
        if (game_state.lives == 0) {
            printf("Game over\n");
        }

        game_state.ball.glued = 1;
        game_state.ball.direction = (Vec3D){0., 0., -1.};
    }
    ball_detect_end_level();
}

void game_init() {
    printf("Game init\n");
    game_state.scene = TITLE_SCREEN;

    game_state.level_selected = 1;

    game_state.paddle.position = (Vec2D){0., 0.};

    game_state.paddle_z_pos = 0;
    game_state.moving_forward = 0;

    game_state.ball.position = (Vec3D){0., 0., -BALL_RADIUS};
    game_state.ball.direction = (Vec3D){0, 0, -1};
    game_state.ball.speed = 1.;
    game_state.ball.glued = 1;
    game_state.ball.glued_offset = (Vec2D){0., 0.};
    
    game_state.glue_enabled = 0;
    load_level_loader("./resources/levels/test.game", &(game_state.levelLoader));

    game_state.lives = 3;   
}

void game_free() {
    printf("Game free\n");
    level_free(&(game_state.level));
}

int game_tick() {
    if (game_state.paused || game_state.scene != GAME) return 0;

    ball_tick();
    if (game_state.moving_forward && !game_state.ball.glued) {
        game_state.paddle_z_pos -= 0.5;
    }
    return 0;
}

void game_start() {
    game_state.n_level = 1;
    load_level(game_state.levelLoader.levels[game_state.levelLoader.current_level], &(game_state.level));
    print_level(&(game_state.level));
    game_state.scene = GAME;
}

void clamp_paddle_position() {
    if (game_state.paddle.position.x - PADDLE_WIDTH / 2 < -CORRIDOR_WIDTH / 2) {
        game_state.paddle.position.x = -CORRIDOR_WIDTH / 2 + PADDLE_WIDTH / 2;
    }
    if (game_state.paddle.position.x + PADDLE_WIDTH / 2 > CORRIDOR_WIDTH / 2) {
        game_state.paddle.position.x = CORRIDOR_WIDTH / 2 - PADDLE_WIDTH / 2;
    }
    if (game_state.paddle.position.y - PADDLE_HEIGHT / 2 < -CORRIDOR_HEIGHT / 2) {
        game_state.paddle.position.y = -CORRIDOR_HEIGHT / 2 + PADDLE_HEIGHT / 2;
    }
    if (game_state.paddle.position.y + PADDLE_HEIGHT / 2 > CORRIDOR_HEIGHT / 2) {
        game_state.paddle.position.y = CORRIDOR_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    }
}